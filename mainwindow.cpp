#include "Image.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMap>
#include <QImage>
#include <iostream>
#include <QFileDialog>
#include <QMouseEvent>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

#include "ViewCompute/NegativeView.h"
#include <ViewCompute/GrayscaleView.h>
#include <ViewCompute/SingleColorView.h>
#include <ViewCompute/BinaryView.h>
#include <ViewCompute/BrightnessView.h>
#include <ViewCompute/BrightnessView.h>
#include <ViewCompute/ContrastView.h>
#include <ViewCompute/HistogramEqualization.h>
#include <ViewCompute/SymmetryTransform.h>
#include <ViewCompute/TransformAngle.h>
#include <ViewCompute/TransformPosition.h>
#include <ViewCompute/MaskFilter.h>
#include <ViewCompute/KernelFilters.h>
#include <ViewCompute/Blur/BlurAverage.h>
#include <ViewCompute/Blur/BlurAverage.h>
#include <ViewCompute/Blur/BlurGaus.h>
#include <ViewCompute/Blur/BlurMedian.h>
#include <ViewCompute/Noise/Noise.h>
#include <ViewCompute/ArithmeticOperations.h>

#include <Windows/AboutDialog.h>
#include <Windows/PlotDialog.h>

using  namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    plotDialog = new PlotDialog(this);
    plotDialog->setModal(false);

    viewContainerWidth = MainWindow::width() - ui->propertyContainer->maximumSize().width();
    viewContainerHeight = MainWindow::height();

    QString path = ":/images/cloud_and_mountain1200.png";
    this->originalImage = Image(path);
    this->processImage = Image(path);

    this->displayImage(this->processImage, ui->label, true);

    QObject::connect(plotDialog, SIGNAL(rejected()), this, SLOT(plotDialogClosed()));

    ui->whiteNoiseCount_Slider->setMaximum(originalImage.width()*originalImage.height()/2);
    ui->blackNoiseCount_Slider->setMaximum(originalImage.width()*originalImage.height()/2);

    ui->kernelWidget->setMainWindow(this);
    ui->arithmeticWidget->setMainWindow(this);
    ui->zoomWidget->setMainWindow(this);
    ui->undoRedoWidget->setMainWindow(this);
    ui->effectsWidget->setMainWindow(this);

//    setInitialImage();
    setStyleSheet();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getViewContainerHeight() {
    return viewContainerHeight;
}

int MainWindow::getViewContainerWidth() {
    return viewContainerWidth;
}

void MainWindow::setViewContainerHeight(int arg) {
    viewContainerHeight = arg;
}

void MainWindow::setViewContainerWidth(int arg) {
    viewContainerWidth = arg;
}

void MainWindow::setInitialImage() {
    QImage img(":/images/cloud_and_mountain1200.png");
    if(img.width() > viewContainerWidth || img.height() > viewContainerHeight) {
        img = img.scaled(viewContainerWidth*zoomFactor, viewContainerHeight*zoomFactor, Qt::KeepAspectRatio);
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::setStyleSheet() {
    ui->binarTresholdRed_Slider->setStyleSheet("QSlider::handle:horizontal { border: 1px solid #777; background:#ff0000;}");
    ui->binarTresholdGreen_Slider->setStyleSheet("QSlider::handle:horizontal { border: 1px solid #777; background:#00ff00;}");
    ui->binarTresholdBlue_Slider->setStyleSheet("QSlider::handle:horizontal { border: 1px solid #777; background:#0000ff;}");
}

void MainWindow::loadImageByPath(QString path) {
    this->originalImage = Image(path);
    this->processImage = Image(path);

    setZoomFactor(1);

    this->updateViewImage(true);

    ui->undoRedoWidget->clearRedoUndoActions();
}

void MainWindow::updateViewImage(bool updateGeometry)
{
    this->displayImage(this->processImage, ui->label, updateGeometry);

    if(plotDialogIsOpen)
        this->updateHistogramEqualization();
}

float MainWindow::getZoomFactor() {
    return zoomFactor;
}

float MainWindow::setZoomFactor(float fact) {
    zoomFactor = fact;
}

void MainWindow::updateHistogramEqualization() {
    plotDialog->updatePlot(&processImage, &originalImage);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);

   setViewContainerWidth(MainWindow::width()  - ui->propertyContainer->maximumSize().width() - 50);
   setViewContainerHeight(MainWindow::height() - 110);
   this->updateViewImage(true);
}

void MainWindow::saveProcessImage()
{
    ui->undoRedoWidget->addToHistory(this->originalImage);

    this->originalImage.copyFrom(&this->processImage);   
}

void MainWindow::applyProcessImage() {
    this->saveProcessImage();
    this->updateViewImage();
}

void MainWindow::revertProcessImage()
{
    this->processImage.copyFrom(&this->originalImage);
    this->updateViewImage();
}

void MainWindow::displayImage(Image img, QLabel* source, bool scaling) {
    viewImage = QPixmap::fromImage(img);

    if(scaling ) {
        if(zoomFactor == 1 && (img.width() > viewContainerWidth || img.height() > viewContainerHeight)) {
            viewImage = viewImage.scaled(viewContainerWidth, viewContainerHeight, Qt::KeepAspectRatio);
        } else if(zoomFactor == 1) {
            viewImage = viewImage.scaled(viewImage.width(), viewImage.height(), Qt::KeepAspectRatio);
        }  else if(zoomFactor == 1.1  && (img.width() < viewContainerWidth && img.height() < viewContainerHeight))  {
            viewImage = viewImage.scaled(viewContainerWidth, viewContainerHeight, Qt::KeepAspectRatio);
        } else {
            viewImage = viewImage.scaled(viewContainerWidth*zoomFactor, viewContainerHeight*zoomFactor, Qt::KeepAspectRatio);
        }
    }

    source->setPixmap(viewImage);
}

void MainWindow::on_brightnessSlider_valueChanged(int value)
{
    BrightnessView::process(&this->originalImage, &this->processImage, value);

    this->setCommonSliderValue(value);
    this->updateViewImage();
}

void MainWindow::contrastInputChanged() {
    int min = ui->contrastMin_spinBox->value();
    int max = ui->contrastMax_spinBox->value();
    ContrastView::processBW(&this->originalImage, &this->processImage, min, max);

    this->updateViewImage();
}

void MainWindow::on_contrastMin_spinBox_valueChanged(int arg1)
{
    if(arg1 < ui->contrastMax_spinBox->value())
        this->contrastInputChanged();
    else
        ui->contrastMin_spinBox->setValue(ui->contrastMax_spinBox->value()-1);
}

void MainWindow::on_contrastMax_spinBox_valueChanged(int arg1)
{
    if(arg1 > ui->contrastMin_spinBox->value())
        this->contrastInputChanged();
    else
        ui->contrastMax_spinBox->setValue(ui->contrastMin_spinBox->value()+1);
}

void MainWindow::on_contrastrgb_Slider_valueChanged(int value)
{
    ContrastView::processRGB(&this->originalImage, &this->processImage, value);

    this->setCommonSliderValue(value);
    this->updateViewImage();
}

void MainWindow::openFile()
{
    QString path = imageFileDialog();

    if(path == "") return;

    this->loadImageByPath(path);
}

void MainWindow::saveFile() {
    this->originalImage.save(this->originalImage.path());
}

void MainWindow::saveFileAs() {
    QString path = QFileDialog::getSaveFileName(nullptr, "Save file", this->originalImage.path(), "*.png *.jpg *.jpeg *.bmp");

    if(path == "") return;

    this->originalImage.save(path);
    this->originalImage.setPath(path);
    this->processImage.setPath(path);
}

void MainWindow::on_actionOpenFile_triggered()
{
   this->openFile();
}

void MainWindow::on_actionSaveFile_triggered()
{
    this->saveFile();
}

void MainWindow::on_actionSave_As_triggered()
{
    this->saveFileAs();
}

void MainWindow::on_actionInfoImage_triggered()
{
    QMessageBox infoBox;
    QString info = QString(""
                           "Image path: %1\n"
                           "Width: %2\n"
                           "Height: %3\n\n"
                           "").arg(
                                this->processImage.path(),
                                QString::number(this->processImage.width()),
                                QString::number(this->processImage.height())
                                );
    infoBox.setText(info);
    infoBox.exec();
}

void MainWindow::setCommonSliderValue(int val) {
    ui->commonSliderLabel->setText(QString::number(val));
}

void MainWindow::on_binarTreshold_Slider_valueChanged(int value)
{
    BinaryView::process(&this->originalImage, &this->processImage, value);

    this->setCommonSliderValue(value);
    this->updateViewImage();
}

void MainWindow::on_action_TransformByHorizontal_triggered()
{
    int step = QInputDialog::getInt(nullptr, "Horizontal offset", "Input the horizontal offset value", QLineEdit::Normal);
    if(step) {
        TransformPosition::transformX(&this->originalImage, &this->processImage, step);
        this->updateViewImage();
    }
}

void MainWindow::on_action_TransformByVertical_triggered()
{
    int step = QInputDialog::getInt(nullptr, "Vertical offset", "Input the vertical offset value", QLineEdit::Normal);
    if(step) {
        TransformPosition::transformY(&this->originalImage, &this->processImage, step);
        this->updateViewImage();
    }
}

void MainWindow::on_action_symmetryHorizontalTransform_triggered()
{
    SymmetryTransform::transformHorizontal(&this->originalImage, &this->processImage);
    this->applyProcessImage();
}

void MainWindow::on_action_symmetryVerticalTransform_triggered()
{
    SymmetryTransform::transformVertical(&this->originalImage, &this->processImage);
    this->applyProcessImage();
}

void MainWindow::on_action_TransformAngleLeft_triggered()
{
    TransformAngle::rotateLeft(&this->originalImage, &this->processImage);
    this->applyProcessImage();
}

void MainWindow::on_action_TransformAngleRight_triggered()
{
    TransformAngle::rotateRight(&this->originalImage, &this->processImage);
    this->applyProcessImage();
}

void MainWindow::on_action_equalizeHist_triggered()
{
    this->plotDialog->show();
    plotDialogIsOpen = true;
    updateHistogramEqualization();
}

void MainWindow::on_action_normalizationImage_triggered()
{
    HistogramEqualization::bwNormalization(&this->processImage);
    this->updateViewImage();
}

void MainWindow::plotDialogClosed() {
    plotDialogIsOpen = false;
}

void MainWindow::on_blurGausSlider_sliderMoved(int pos)
{
    this->setCommonSliderValue(pos);
}

void MainWindow::on_blurAverage_Slider_sliderMoved(int position)
{
    this->setCommonSliderValue(position);
}

void MainWindow::on_blurAverage_Slider_sliderReleased()
{
    int value = ui->blurAverage_Slider->value();

    if(value <= 0) {
        this->revertProcessImage();
        return;
    }

    BlurAverage::proccess(&this->originalImage, &this->processImage, value);

    this->updateViewImage();
}

void MainWindow::on_blurGaus_apply_clicked()
{
    BlurGaus::proccess(&this->originalImage, &this->processImage, 5);

    this->updateViewImage();
}

void MainWindow::on_whiteNoiseCount_Slider_sliderMoved(int position)
{
    this->revertProcessImage();

    Noise::proccess(&this->originalImage, &this->processImage, position, ui->blackNoiseCount_Slider->value());

    this->updateViewImage();
    this->setCommonSliderValue(position);
}

void MainWindow::on_blackNoiseCount_Slider_sliderMoved(int position)
{
    this->revertProcessImage();

    Noise::proccess(&this->originalImage, &this->processImage, ui->whiteNoiseCount_Slider->value(), position);

    this->updateViewImage();
    this->setCommonSliderValue(position);
}

void MainWindow::on_commandLinkButton_medianSquare_clicked()
{
    BlurMedian::square(&this->originalImage, &this->processImage);

    this->updateViewImage();
}

void MainWindow::on_bioNoiseCount_Slider_sliderMoved(int position)
{
    this->revertProcessImage();

    Noise::bipolar(&this->originalImage, &this->processImage, position);

    this->updateViewImage();
    this->setCommonSliderValue(position);
}

void MainWindow::on_commandLinkButton_medianSquare_2_clicked()
{
    BlurMedian::adaptiveSquare(&this->originalImage, &this->processImage, 3);

    this->updateViewImage();
}

void MainWindow::on_btn_revert_processImage_clicked()
{
    this->revertProcessImage();
}

void MainWindow::on_btn_medianCross_clicked()
{
    BlurMedian::cross(&this->originalImage, &this->processImage);

    this->updateViewImage();
}

void MainWindow::on_btn_adaptiveMedianCross_clicked()
{
    BlurMedian::adaptiveCross(&this->originalImage, &this->processImage);

    this->updateViewImage();
}

void MainWindow::processColorBinary(int rPos, int gPos, int bPos) {
    BinaryView::binaryColor(&this->originalImage, &this->processImage, rPos, gPos, bPos);
}

void MainWindow::on_binarTresholdRed_Slider_sliderMoved(int position)
{
    processColorBinary(
                ui->binarTresholdRed_Slider->value(),
                ui->binarTresholdGreen_Slider->value(),
                ui->binarTresholdBlue_Slider->value());

    this->updateViewImage();
    this->setCommonSliderValue(position);
}

void MainWindow::on_binarTresholdGreen_Slider_sliderMoved(int position)
{
    processColorBinary(
                ui->binarTresholdRed_Slider->value(),
                ui->binarTresholdGreen_Slider->value(),
                ui->binarTresholdBlue_Slider->value());

    this->updateViewImage();
    this->setCommonSliderValue(position);
}

void MainWindow::on_binarTresholdBlue_Slider_sliderMoved(int position)
{
    processColorBinary(
                ui->binarTresholdRed_Slider->value(),
                ui->binarTresholdGreen_Slider->value(),
                ui->binarTresholdBlue_Slider->value());

    this->updateViewImage();
    this->setCommonSliderValue(position);
}

void MainWindow::on_horizontalSlider_speedBlur_sliderReleased()
{
    int size = ui->horizontalSlider_speedBlur->value();
    float mask[31][31];

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            mask[i][j] = 0;

    float k = 1.0f/size;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++) {
            if(i == j)
                mask[i][j] = k;
        }


    MaskFilter::proccess(&this->originalImage, &this->processImage, size, mask);

    this->updateViewImage();
}

void MainWindow::on_horizontalSlider_speedBlur_valueChanged(int value)
{
     setCommonSliderValue(value);
}

QString MainWindow::imageFileDialog() {
    QString path = QFileDialog::getOpenFileName(nullptr, "Choose file", "", "*.png *.jpg *.jpeg *.bmp");

    return path;
}

Image *MainWindow::getOriginalImage()
{
    return &this->originalImage;
}

Image *MainWindow::getProcessImage()
{
    return  &this->processImage;
}

void MainWindow::on_commandLinkButton_dilate_clicked()
{
    ArithmeticOperations::dilate(&this->originalImage, &this->processImage);

    this->updateViewImage();
}

void MainWindow::on_commandLinkButton_erosion_clicked()
{
    ArithmeticOperations::erosion(&this->originalImage, &this->processImage);

    this->updateViewImage();
}

void MainWindow::on_actionAbout_triggered()
{
    QDialog* dialog = new AboutDialog(this);
    dialog->exec();
}

void MainWindow::on_applyChanges_btn_clicked()
{
    this->applyProcessImage();
}
