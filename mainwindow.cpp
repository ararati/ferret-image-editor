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
#include <ViewCompute/Blur/BlurMedian.h>

#include <ViewCompute/Noise/Noise.h>
#include <ViewCompute/ArithmeticOperations.h>

using  namespace std;
//using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    plotDialog = new PlotDialog(this);
    plotDialog->setModal(false);

    QString path = ":/images/Lenna.png";
    this->originalImage = Image(path);
    this->processImage = Image(path);

    originalImageWidth =  ui->label->width();
    originalImageHeight = ui->label->height();

    this->displayImage(this->processImage, ui->label, true);

    QList<QString> viewType;
    viewType = {"Обычное", "Негатив", "Чёрно-белое", "Одноцветное Red", "Одноцветное Green", "Одноцветное Blue"};

    foreach(QString type, viewType) {
        ui->viewTypeComboBox->addItem(type);
    }

    this->setMouseTracking(true);
    installEventFilter(this);

    QImage img(":/images/Lenna.png");

    if(img.width() > ui->label->width() || img.height() > ui->label->height()) {
        img = img.scaled(ui->label->width()*zoomFactor, ui->label->height()*zoomFactor, Qt::KeepAspectRatio);
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

    imageViewWidth = ui->label->geometry().width();
    imageViewHeight = ui->label->geometry().height();

//    ui->scrollArea->setWidgetResizable(true);
//    ui->scrollArea->takeWidget();
//    ui->scrollArea->setWidget(ui->widget_2);

    ui->binarTresholdRed_Slider->setStyleSheet("QSlider::handle:horizontal { border: 1px solid #777; background:#ff0000;}");
    ui->binarTresholdGreen_Slider->setStyleSheet("QSlider::handle:horizontal { border: 1px solid #777; background:#00ff00;}");
    ui->binarTresholdBlue_Slider->setStyleSheet("QSlider::handle:horizontal { border: 1px solid #777; background:#0000ff;}");




    QList<QString> arithmeticOperations;
    arithmeticOperations = {"Сумма", "Разность", "Умножение", "Среднее", "Мин", "Макс", "OR", "AND", "XOR"};

    foreach(QString op, arithmeticOperations) {
        ui->arithmeticOperations_comboBox->addItem(op);
    }

//    int i = 50, j = 15;
//    QRgb px = this->originalImage.pixel(i, j);
//    QMessageBox infoBox;
//    QString info = QString("Pixel on (50, 15) has color: \n"
//                           "R: %1\n"
//                           "G: %2\n"
//                           "B: %3\n"
//                           "").arg(
//                                QString::number(qRed(px)),
//                                QString::number(qGreen(px)),
//                                QString::number(qBlue(px))
//                                );
//    infoBox.setText(info);
//    infoBox.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImageByPath(QString path) {
    this->originalImage = Image(path);
    this->processImage = Image(path);

    zoomFactor = 1;

    this->updateViewImage(true);

    clearRedoUndoActions();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
//    scrollX++;
  if (event->type() == QEvent::MouseMove)
  {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    if(mouseEvent->pos().x() < ui->label->geometry().x() || mouseEvent->pos().y() < ui->label->geometry().y())
        return false;
    int x =   mouseEvent->pos().x();
    int y =   mouseEvent->pos().y();

    ui->xPos_label->setText(QString::number(x));
    ui->yPos_label->setText(QString::number(y));
//    this->updateRgbStatus(x, y);
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

void MainWindow::updateViewImage(bool updateGeometry)
{
    this->displayImage(this->processImage, ui->label, updateGeometry);

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

    plot->legend->setVisible(true);
    plot->addGraph();
    plot->graph(0)->setPen(QPen(QColor(0, 0, 255)));
    plot->graph(0)->setName("Обрабатываемое");
    plot->addGraph();
    plot->graph(1)->setPen(QPen(QColor(255, 0, 0)));
    plot->graph(1)->setName("Сохраненное");

    plot->xAxis->setLabel("brightness");
    plot->yAxis->setLabel("intensity");

    plot->xAxis->setRange(0, 255);
    plot->yAxis->setRange(0, maxY);

    plot->graph(0)->setData(x, y);
    plot->graph(1)->setData(x, y2);
    plot->replot();
    plot->clearPlottables();


}

void MainWindow::saveProcessImage()
{
    pastActions.push(this->originalImage);
    this->originalImage.copyFrom(&this->processImage);

    ui->btn_back_action->setDisabled(pastActions.count() == 0);
    ui->btn_redo_action->setDisabled(redoActions.count() == 0);
}

void MainWindow::revertProcessImage()
{
    this->processImage.copyFrom(&this->originalImage);
    this->updateViewImage();
}

void MainWindow::displayImage(Image img, QLabel* source, bool scaling) {
    viewImage = QPixmap::fromImage(img);

//    if(img.width() > source->width() || img.height() > source->height()) {
    if(scaling ) {
        if(zoomFactor > 1 || (img.width() > originalImageWidth || img.height() > originalImageWidth)) {
            viewImage = viewImage.scaled(originalImageWidth*zoomFactor, originalImageWidth*zoomFactor, Qt::KeepAspectRatio);
        }
    }
//    viewImage.scroll(scrollX, 0, viewImage.rect());
    //    }

    source->setPixmap(viewImage);
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
    QString path = imageFileDialog();

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
//    QWidget *newTab = new QWidget(ui->imagesTabs);
//    QLabel* imgLabel = new QLabel("abc", newTab);
//    imgLabel->show();
//    ui->imagesTabs->addTab(newTab, name);
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
//    this->saveProcessImage();
//    this->updateViewImage();
}

void MainWindow::on_contrastrgb_Slider_sliderReleased()
{
//    this->saveProcessImage();
//    this->updateViewImage();
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
//    this->saveProcessImage();
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
//    int value = ui->blurGausSlider->value();

//    if(value <= 0) {
//        this->revertProcessImage();
//        return;
//    }

//    BlurGaus::proccess(&this->originalImage, &this->processImage, 5);

//    this->updateViewImage();
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
    int maskSize = (ui->radioButton_mask3x3->isChecked()) ? 3 : 5;

    float mask[31][31];

    mask[0][0] = ui->sharpMask00->value();
    mask[1][0] = ui->sharpMask10->value();
    mask[2][0] = ui->sharpMask20->value();

    mask[0][1] = ui->sharpMask01->value();
    mask[1][1] = ui->sharpMask11->value();
    mask[1][2] = ui->sharpMask12->value();

    mask[0][2] = ui->sharpMask02->value();
    mask[1][2] = ui->sharpMask12->value();
    mask[2][2] = ui->sharpMask22->value();

    if(maskSize == 5) {
        mask[0][3] = ui->sharpMask03->value();
        mask[0][4] = ui->sharpMask04->value();

        mask[1][3] = ui->sharpMask13->value();
        mask[1][4] = ui->sharpMask14->value();

        mask[2][3] = ui->sharpMask23->value();
        mask[2][4] = ui->sharpMask24->value();

        mask[3][0] = ui->sharpMask30->value();
        mask[3][1] = ui->sharpMask31->value();
        mask[3][2] = ui->sharpMask32->value();
        mask[3][3] = ui->sharpMask33->value();
        mask[3][4] = ui->sharpMask34->value();

        mask[4][0] = ui->sharpMask40->value();
        mask[4][1] = ui->sharpMask41->value();
        mask[4][2] = ui->sharpMask42->value();
        mask[4][3] = ui->sharpMask43->value();
        mask[4][4] = ui->sharpMask44->value();
    }

    MaskFilter::proccess(&this->originalImage, &this->processImage, maskSize, mask, ui->maskFactor_SpinBox->value(), ui->maskBias_SpinBox->value());

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

void MainWindow::clearRedoUndoActions() {
    redoActions.clear();
    pastActions.clear();
    ui->btn_back_action->setDisabled(pastActions.count() == 0);
    ui->btn_redo_action->setDisabled(redoActions.count() == 0);
}

void MainWindow::on_btn_back_action_clicked()
{
    redoActions.clear();
    redoActions.push(this->originalImage);

    QImage img = pastActions.pop();

    this->processImage.copyFrom(&img);
    this->originalImage.copyFrom(&this->processImage);
    this->updateViewImage();

    ui->btn_back_action->setDisabled(pastActions.count() == 0);
    ui->btn_redo_action->setDisabled(redoActions.count() == 0);
}

void MainWindow::on_btn_redo_action_clicked()
{
    QImage img = redoActions.pop();

    pastActions.push(this->originalImage);
    this->processImage.copyFrom(&img);
    this->originalImage.copyFrom(&this->processImage);
    this->updateViewImage();

    ui->btn_back_action->setDisabled(pastActions.count() == 0);
    ui->btn_redo_action->setDisabled(redoActions.count() == 0);
}

void MainWindow::on_commandLinkButton_clicked()
{
    if(zoomFactor < 7) {
        zoomFactor *= 1.5;
        this->updateViewImage(true);
    }
    qInfo() << zoomFactor;

    ui->commandLinkButton->setDisabled(zoomFactor >= 7);
    ui->btn_zoom_out->setDisabled(zoomFactor == 1);
//    ui->label->setScaledContents(true);
//    ui->label->setGeometry(ui->label->geometry().x(), ui->label->geometry().y(), imageViewWidth*zoomFactor, imageViewHeight*zoomFactor);
}

void MainWindow::on_btn_zoom_out_clicked()
{
    zoomFactor = (zoomFactor*0.5 <= 1) ? 1 : zoomFactor * 0.5;
    this->updateViewImage(true);
    qInfo() << zoomFactor;
    ui->btn_zoom_out->setDisabled(zoomFactor == 1);
    ui->commandLinkButton->setDisabled(zoomFactor >= 7);
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

void MainWindow::toggleMask5x5() {
    ui->sharpMask03->setEnabled(!ui->sharpMask03->isEnabled());
    ui->sharpMask04->setEnabled(!ui->sharpMask04->isEnabled());

    ui->sharpMask13->setEnabled(!ui->sharpMask13->isEnabled());
    ui->sharpMask14->setEnabled(!ui->sharpMask14->isEnabled());

    ui->sharpMask23->setEnabled(!ui->sharpMask23->isEnabled());
    ui->sharpMask24->setEnabled(!ui->sharpMask24->isEnabled());

    ui->sharpMask30->setEnabled(!ui->sharpMask30->isEnabled());
    ui->sharpMask31->setEnabled(!ui->sharpMask31->isEnabled());
    ui->sharpMask32->setEnabled(!ui->sharpMask32->isEnabled());
    ui->sharpMask33->setEnabled(!ui->sharpMask33->isEnabled());
    ui->sharpMask34->setEnabled(!ui->sharpMask34->isEnabled());

    ui->sharpMask40->setEnabled(!ui->sharpMask40->isEnabled());
    ui->sharpMask41->setEnabled(!ui->sharpMask41->isEnabled());
    ui->sharpMask42->setEnabled(!ui->sharpMask42->isEnabled());
    ui->sharpMask43->setEnabled(!ui->sharpMask43->isEnabled());
    ui->sharpMask44->setEnabled(!ui->sharpMask44->isEnabled());
}

void MainWindow::on_radioButton_mask5x5_clicked()
{
    toggleMask5x5();
}

void MainWindow::on_radioButton_mask3x3_clicked()
{
    toggleMask5x5();
}

void MainWindow::on_horizontalSlider_speedBlur_sliderReleased()
{
    int size = ui->horizontalSlider_speedBlur->value();
    float mask[31][31];

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            mask[i][j] = 0;

    double k = 1.0f/size;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++) {
            if(i == j)
                mask[i][j] = k;
        }


    MaskFilter::proccess(&this->originalImage, &this->processImage, size, mask, ui->maskFactor_SpinBox->value(), ui->maskBias_SpinBox->value());

    this->updateViewImage();
}

void MainWindow::on_horizontalSlider_speedBlur_valueChanged(int value)
{
     setCommonSliderValue(value);
}

QString MainWindow::imageFileDialog() {
    QString path = QFileDialog::getOpenFileName(0, "Choose file", "", "*.png *.jpg *.jpeg *.bmp");

    return path;
}

void MainWindow::on_arithmeticImgLoad_pushButton_clicked()
{
    this->revertProcessImage();

    QString path = imageFileDialog();
    if(path == "") return;

    //TODO: For refactoring
    if(ui->aritmeticImgSize_checkBox->isChecked()) {
        arithmeticImage = Image(originalImage);
        QImage img = QImage(path);
        img = img.scaled(originalImage.width(), originalImage.height());
        arithmeticImage.copyFrom(&img);
    } else arithmeticImage = Image(path);

    QPixmap pix = QPixmap::fromImage(arithmeticImage).scaled(ui->arithmeticImg_label->width(),ui->arithmeticImg_label->height(),Qt::KeepAspectRatio);

    ui->arithmeticImg_label->setPixmap(pix);

    processArithmeticOperation(ui->arithmeticOperations_comboBox->currentText());

    this->updateViewImage();
}

void MainWindow::processArithmeticOperation(QString arg1) {
    if(arg1 == "Сумма")
        ArithmeticOperations::sum(&this->originalImage, &this->processImage, &this->arithmeticImage);
    else if(arg1 == "Разность")
        ArithmeticOperations::diff(&this->originalImage, &this->processImage, &this->arithmeticImage);
    else if(arg1 == "Умножение")
        ArithmeticOperations::mul(&this->originalImage, &this->processImage, &this->arithmeticImage);
    else if(arg1 == "Среднее")
        ArithmeticOperations::average(&this->originalImage, &this->processImage, &this->arithmeticImage);
    else if(arg1 == "Мин")
        ArithmeticOperations::min(&this->originalImage, &this->processImage, &this->arithmeticImage);
    else if(arg1 == "Макс")
        ArithmeticOperations::max(&this->originalImage, &this->processImage, &this->arithmeticImage);
    else if(arg1 == "OR")
        ArithmeticOperations::OR(&this->originalImage, &this->processImage, &this->arithmeticImage);
    else if(arg1 == "AND")
        ArithmeticOperations::AND(&this->originalImage, &this->processImage, &this->arithmeticImage);
    else if(arg1 == "XOR")
        ArithmeticOperations::XOR(&this->originalImage, &this->processImage, &this->arithmeticImage);
}

void MainWindow::on_arithmeticOperations_comboBox_currentTextChanged(const QString &arg1)
{
    processArithmeticOperation(arg1);

    this->updateViewImage();
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
