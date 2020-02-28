#include "Helper.h"
#include "image.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMap>

#include <QImage>
#include <iostream>
#include <QFileDialog>
#include <QMouseEvent>
#include <QMessageBox>
#include <QInputDialog>

//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
#include<QDebug>
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


#include <Windows/PlotDialog.h>

#include <ViewCompute/Blur/BlurAverage.h>
#include <ViewCompute/Blur/BlurAverage.h>
#include <ViewCompute/Blur/BlurGaus.h>

#include <ViewCompute/Noise/Noise.h>

using  namespace std;
//using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    plotDialog = new PlotDialog(this);
    plotDialog->setModal(false);

    QString path = ":/images/home.jpg";
    this->originalImage = Image(path);
    this->processImage = Image(path);

    this->displayImage(this->processImage, ui->label);

    QList<QString> viewType;
    viewType = {"Обычное", "Негатив", "Чёрно-белое", "Одноцветное Red", "Одноцветное Green", "Одноцветное Blue"};

    foreach(QString type, viewType) {
        ui->viewTypeComboBox->addItem(type);
    }

    this->setMouseTracking(true);
    installEventFilter(this);

    QImage img(":/images/home.jpg");

    if(img.width() > ui->label->width() || img.height() > ui->label->height()) {
        img = img.scaled(ui->label->width(), ui->label->height(), Qt::KeepAspectRatio);
    }

    ui->label->setPixmap(QPixmap::fromImage(img));

    QObject::connect(plotDialog, SIGNAL(rejected()), this, SLOT(plotDialogClosed()));

    QList<QString> filters;
    filters = {"Обнулить матрицу", "Размытие", "Резкость", "Горизонтальные линии", "Собель: левая граница", "Собель: правая граница", "Собель: верхняя граница", "Собель: нижняя граница"};

    foreach(QString type, filters) {
        ui->masks_ComboBox->addItem(type);
    }

    ui->whiteNoiseCount_Slider->setMaximum(originalImage.width()*originalImage.height()/2);
    ui->blackNoiseCount_Slider->setMaximum(originalImage.width()*originalImage.height()/2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImageByPath(QString path) {
    this->originalImage = Image(path);
    this->processImage = Image(path);

    this->updateViewImage();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::MouseMove)
  {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    int x =  mouseEvent->pos().x();
    int y =  mouseEvent->pos().y();

    this->updateRgbStatus(x, y);
    //statusBar()->showMessage(QString("Mouse move (%1,%2)").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y()));
  };
  return false;
}

void MainWindow::updateRgbStatus(int x, int y) {
    uint height = this->processImage.width(), width = this->processImage.height();

    if(x > width || x < 0 || y < 0 || y > height)
        return;

//    Vec3b pix = this->processImage.getCvImg().at<Vec3b>(x, y);
//    ui->rgbStatus_Label->setText("rgb(" + QString::number(pix[0]) + ", " + QString::number(pix[1]) + ", " + QString::number(pix[2]) + ")");
//    ui->xPos_label->setText(QString::number(x));
//    ui->yPos_label->setText(QString::number(y));
}

void MainWindow::updateViewImage()
{
    this->displayImage(this->processImage, ui->label);

    if(plotDialogIsOpen)
        this->updateHistogramEqualization();
}

void MainWindow::updateHistogramEqualization() {
    QVector<double> x(256);
    for(int i =  0; i < 256; i++) {
        x[i] = i;
    }
    QVector<double> y = HistogramEqualization::bwBrightnessData(&this->processImage);
    QVector<double> y2 = HistogramEqualization::bwBrightnessData(&this->originalImage);

    double maxY = *std::max_element(y.constBegin(), y.constEnd());
    double maxY2 = *std::max_element(y2.constBegin(), y2.constEnd());
    maxY = max(maxY, maxY2);

    QCustomPlot* plot = plotDialog->getPlot();

    plot->addGraph();
    plot->graph(0)->setPen(QPen(QColor(0, 0, 255)));
    plot->addGraph();
    plot->graph(1)->setPen(QPen(QColor(255, 0, 0)));

    plot->xAxis->setLabel("brightness");
    plot->yAxis->setLabel("intensity");

    plot->xAxis->setRange(0, 255);
    plot->yAxis->setRange(0, maxY);

    QCPBars *newBars = new QCPBars(plot->xAxis, plot->yAxis);

    newBars->setName("Image brightness");
    plot->graph(0)->setData(x, y);
    plot->graph(1)->setData(x, y2);
    plot->replot();
    plot->clearPlottables();
}

void MainWindow::saveProcessImage()
{
    this->originalImage.copyFrom(&this->processImage);
}

void MainWindow::revertProcessImage()
{
    this->processImage.copyFrom(&this->originalImage);
    this->updateViewImage();
}

void MainWindow::displayImage(Image img, QLabel* source) {
    QPixmap qImg = QPixmap::fromImage(img);

    if(img.width() > source->width() || img.height() > source->height()) {
        qImg = qImg.scaled(source->width(), source->height(), Qt::KeepAspectRatio);
    }

    source->setPixmap(qImg);
}

void MainWindow::processViewType(QString type) {
    if(type == "Обычное") {
        this->revertProcessImage();
    } else if(type == "Негатив") {
        NegativeView::process(&this->originalImage, &this->processImage);
    } else if(type == "Чёрно-белое") {
        GrayscaleView::process(&this->originalImage, &this->processImage);
    } else if(type == "Одноцветное Red") {
        SingleColorView::process(&this->originalImage, &this->processImage, 0);
    } else if(type == "Одноцветное Green") {
        SingleColorView::process(&this->originalImage, &this->processImage, 1);
    } else if(type == "Одноцветное Blue") {
        SingleColorView::process(&this->originalImage, &this->processImage, 2);
    }
}

void MainWindow::on_viewTypeComboBox_currentTextChanged(const QString &arg1)
{
    this->processViewType(arg1);
    this->updateViewImage();
}

//Brightness
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


//RGB contrast
void MainWindow::on_contrastrgb_Slider_valueChanged(int value)
{
    ContrastView::processRGB(&this->originalImage, &this->processImage, value);

    this->setCommonSliderValue(value);

    this->updateViewImage();
}

void MainWindow::on_viewType_btn_clicked()
{
    this->saveProcessImage();
    ui->viewTypeComboBox->setCurrentIndex(0);
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(0, "Choose file", "", "*.png *.jpg *.jpeg *.bmp");

    if(path == "") return;

    this->loadImageByPath(path);
}

void MainWindow::saveFile() {
    this->originalImage.save(this->originalImage.path());
//    imwrite(this->originalImage.path(), this->originalImage.getCvImg());
}

void MainWindow::saveFileAs() {
    QString path = QFileDialog::getSaveFileName(0, "Save file", this->originalImage.path(), "*.png *.jpg *.jpeg *.bmp");

    if(path == "") return;

    this->originalImage.save(path);
//    imwrite(path.toStdString(), this->originalImage.getCvImg());
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

                           "Channels: %4\n"
                           "Depth: %5\n"
                           "").arg(
                                this->processImage.path(),
                                QString::number(this->processImage.width()),
                                QString::number(this->processImage.height())

//                                QString::number(this->processImage.getCvImg().channels()),
//                                QString::number(this->processImage.getCvImg().depth())
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
    int step = QInputDialog::getInt(0, "Смещения по горизонтали", "Введите значение смещения по горизонтали", QLineEdit::Normal);
    if(step) {
        TransformPosition::transformX(&this->originalImage, &this->processImage, step);
        //this->saveProcessImage();
        this->updateViewImage();
    }
}

void MainWindow::on_action_TransformByVertical_triggered()
{
    int step = QInputDialog::getInt(0, "Смещения по вертикали", "Введите значение смещения по вертикали", QLineEdit::Normal);
    if(step) {
        TransformPosition::transformY(&this->originalImage, &this->processImage, step);
        //this->saveProcessImage();
        this->updateViewImage();
    }
}

void MainWindow::on_action_symmetryHorizontalTransform_triggered()
{
    SymmetryTransform::transformHorizontal(&this->originalImage, &this->processImage);
    this->saveProcessImage();
    this->updateViewImage();
}

void MainWindow::on_action_symmetryVerticalTransform_triggered()
{
    SymmetryTransform::transformVertical(&this->originalImage, &this->processImage);
    this->saveProcessImage();
    this->updateViewImage();
}

void MainWindow::on_action_TransformAngleLeft_triggered()
{
    TransformAngle::rotateLeft(&this->originalImage, &this->processImage);
    this->saveProcessImage();
    this->updateViewImage();
}

void MainWindow::on_action_TransformAngleRight_triggered()
{
    TransformAngle::rotateRight(&this->originalImage, &this->processImage);
    this->saveProcessImage();
    this->updateViewImage();
}

void MainWindow::addImageTab(QString name) {
    QWidget *newTab = new QWidget(ui->imagesTabs);
    QLabel* imgLabel = new QLabel("abc", newTab);
    imgLabel->show();
    ui->imagesTabs->addTab(newTab, name);
}

void MainWindow::on_actionNewFile_triggered()
{
    this->addImageTab("New image");
}

void MainWindow::on_imagesTabs_currentChanged(int index)
{

}

void MainWindow::on_brightnessSlider_sliderReleased()
{
    this->saveProcessImage();
    this->updateViewImage();
}

void MainWindow::on_contrastrgb_Slider_sliderReleased()
{
    this->saveProcessImage();
    this->updateViewImage();
}

void MainWindow::on_contrastBW_okBtn_clicked()
{
    this->saveProcessImage();
    this->updateViewImage();
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
    this->saveProcessImage();
    this->updateViewImage();
}

void MainWindow::plotDialogClosed() {
    plotDialogIsOpen = false;
}

void MainWindow::on_action_averageBlur_triggered()
{
//    BlurAverage::proccess(&this->originalImage, &this->processImage, 44);
//    this->saveProcessImage();
//    this->updateViewImage();
}

void MainWindow::on_blurGausSlider_sliderReleased()
{
    int value = ui->blurGausSlider->value();

    if(value <= 0) {
        this->revertProcessImage();
        return;
    }

    BlurGaus::proccess(&this->originalImage, &this->processImage, 5);

    this->updateViewImage();
}

void MainWindow::on_blurGausSlider_sliderMoved(int pos)
{
    this->setCommonSliderValue(pos);
}

void MainWindow::on_blurGaus_saveBtn_clicked()
{
    ui->blurAverage_Slider->setValue(0);
    this->saveProcessImage();
    this->updateViewImage();
}

void MainWindow::on_blurAverage_saveBtn_clicked()
{
    this->saveProcessImage();
    this->updateViewImage();
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

void MainWindow::on_sharpMask_saveBtn_clicked()
{
    this->saveProcessImage();
    this->updateViewImage();
}

void MainWindow::on_masks_ComboBox_currentTextChanged(const QString &arg1)
{
    double mask[3][3];
    if(arg1 == "Собель: левая граница")
        KernelFilters::leftSobel(mask);
    else if(arg1 == "Размытие")
        KernelFilters::smooth(mask);
    else if(arg1 == "Горизонтальные линии")
        KernelFilters::horizontalLines(mask);
    else if(arg1 == "Резкость")
        KernelFilters::sharpen(mask);
    else if(arg1 == "Собель: правая граница")
        KernelFilters::rightSobel(mask);
    else if(arg1 == "Собель: нижняя граница")
        KernelFilters::bottomSobel(mask);
    else if(arg1 == "Собель: верхняя граница")
        KernelFilters::topSobel(mask);
    else KernelFilters::zeros(mask);;

    ui->sharpMask00->setValue(mask[0][0]);
    ui->sharpMask10->setValue(mask[1][0]);
    ui->sharpMask20->setValue(mask[2][0]);

    ui->sharpMask01->setValue(mask[0][1]);
    ui->sharpMask11->setValue(mask[1][1]);
    ui->sharpMask12->setValue(mask[1][2]);

    ui->sharpMask02->setValue(mask[0][2]);
    ui->sharpMask21->setValue(mask[2][1]);
    ui->sharpMask22->setValue(mask[2][2]);
}

void MainWindow::on_blurGaus_apply_clicked()
{
    BlurGaus::proccess(&this->originalImage, &this->processImage, 5);

    this->updateViewImage();
}

void MainWindow::on_sharpMask_applyBtn_clicked()
{
    float mask[3][3];

    mask[0][0] = ui->sharpMask00->value();
    mask[1][0] = ui->sharpMask10->value();
    mask[2][0] = ui->sharpMask20->value();

    mask[0][1] = ui->sharpMask01->value();
    mask[1][1] = ui->sharpMask11->value();
    mask[1][2] = ui->sharpMask12->value();

    mask[0][2] = ui->sharpMask02->value();
    mask[1][2] = ui->sharpMask12->value();
    mask[2][2] = ui->sharpMask22->value();

    MaskFilter::proccess(&this->originalImage, &this->processImage, mask, ui->maskFactor_SpinBox->value(), ui->maskBias_SpinBox->value());

    this->updateViewImage();
}

void MainWindow::on_rndNoise_saveBtn_clicked()
{
        this->saveProcessImage();
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

void MainWindow::on_binarization_saveBtn_clicked()
{
    this->saveProcessImage();
    this->updateViewImage();
}
