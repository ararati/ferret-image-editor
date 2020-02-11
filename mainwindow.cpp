#include "Helper.h"
#include "image.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <iostream>
#include <QFileDialog>
#include <QMouseEvent>
#include <QMessageBox>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include<QDebug>
#include "ViewCompute/NegativeView.h"
#include <ViewCompute/GrayscaleView.h>
#include <ViewCompute/SingleColorView.h>

#include <ViewCompute/BinaryView.h>
#include <ViewCompute/BrightnessView.h>
#include <ViewCompute/BrightnessView.h>
#include <ViewCompute/ContrastView.h>
#include <ViewCompute/SymmetryTransform.h>
#include <ViewCompute/TransformPosition.h>

using  namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    string path = "D:\\home.jpg";
    this->originalImage = Image(path);
    this->processImage = Image(path);

//    ui->label->setScaledContents(true);
    this->displayImage(this->processImage, ui->label);

    QList<QString> viewType;
    viewType = {"Обычное", "Негатив", "Чёрно-белое", "Одноцветное Red", "Одноцветное Green", "Одноцветное Blue"};

    foreach(QString type, viewType) {
        ui->viewTypeComboBox->addItem(type);
    }

    this->setMouseTracking(true);
    installEventFilter(this);

//    this->actionEvent()->
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImageByPath(string path) {
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
    uint height = this->processImage.getWidth(), width = this->processImage.getHeight();

    if(x > width || x < 0 || y < 0 || y > height)
        return;

    Vec3b pix = this->processImage.getCvImg().at<Vec3b>(x, y);
    ui->rgbStatus_Label->setText("rgb(" + QString::number(pix[0]) + ", " + QString::number(pix[1]) + ", " + QString::number(pix[2]) + ")");
}

void MainWindow::updateViewImage()
{
    this->displayImage(this->processImage, ui->label);
}

void MainWindow::saveProcessImage()
{
    this->processImage.getCvImg().copyTo(this->originalImage.getCvImg());
}

void MainWindow::revertProcessImage()
{
    this->originalImage.getCvImg().copyTo(this->processImage.getCvImg());
}

void MainWindow::displayImage(Image img, QLabel* source) {
    QPixmap qImg = QPixmap::fromImage(img.toQImage());

    if(img.getWidth() > source->width() || img.getHeight() > source->height()) {
        qImg = qImg.scaled(source->width(), source->height(), Qt::KeepAspectRatio);
        qInfo() << "scaled";
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
        SingleColorView::process(&this->originalImage, &this->processImage, 2);
    } else if(type == "Одноцветное Green") {
        SingleColorView::process(&this->originalImage, &this->processImage, 1);
    } else if(type == "Одноцветное Blue") {
        SingleColorView::process(&this->originalImage, &this->processImage, 0);
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

    this->updateViewImage();
}

void MainWindow::on_brightnessOk_btn_clicked()
{
    this->saveProcessImage();
    ui->brightnessSlider->setValue(0);
}

//Contrast
void MainWindow::on_contrastOk_btn_clicked()
{
    this->saveProcessImage();
    ui->contrastMin_spinBox->setValue(0);
    ui->contrastMax_spinBox->setValue(255);
}

void MainWindow::contrastInputChanged() {
    int min = ui->contrastMin_spinBox->value();
    int max = ui->contrastMax_spinBox->value();
    ContrastView::processBW(&this->originalImage, &this->processImage, min, max);

    this->updateViewImage();
}

void MainWindow::on_contrastMin_spinBox_valueChanged(int arg1)
{
    this->contrastInputChanged();
}

void MainWindow::on_contrastMax_spinBox_valueChanged(int arg1)
{
    this->contrastInputChanged();
}


//RGB contrast
void MainWindow::on_contrastrgb_Slider_valueChanged(int value)
{
    ContrastView::processRGB(&this->originalImage, &this->processImage, value);

    this->updateViewImage();
}

void MainWindow::on_contrastrgbOk_btn_clicked()
{
    this->saveProcessImage();
    ui->contrastrgb_Slider->setValue(0);
}

void MainWindow::on_discard_pushButton_clicked()
{
    this->revertProcessImage();
}

void MainWindow::on_viewType_btn_clicked()
{
    this->saveProcessImage();
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(0, "Choose file", "", "*.png *.jpg *.jpeg *.bmp");

    if(path == "") return;

    this->loadImageByPath(path.toStdString());
}

void MainWindow::saveFile() {
    imwrite(this->originalImage.getPath(), this->originalImage.getCvImg());
}

void MainWindow::saveFileAs() {
    QString path = QFileDialog::getSaveFileName(0, "Save file", QString::fromStdString(this->originalImage.getPath()), "*.png *.jpg *.jpeg *.bmp");

    if(path == "") return;

    imwrite(path.toStdString(), this->originalImage.getCvImg());
    this->originalImage.setPath(path.toStdString());
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
                                QString::fromStdString(this->processImage.getPath()),
                                QString::number(this->processImage.getWidth()),
                                QString::number(this->processImage.getHeight()),

                                QString::number(this->processImage.getCvImg().channels()),
                                QString::number(this->processImage.getCvImg().depth())
                                );
    infoBox.setText(info);
    infoBox.exec();
}

void MainWindow::on_binarTreshold_Slider_valueChanged(int value)
{
    BinaryView::process(&this->originalImage, &this->processImage, value);

    this->updateViewImage();
}

void MainWindow::on_action_TransformByHorizontal_triggered()
{
    TransformPosition::transformX(&this->originalImage, &this->processImage, -100);
    this->updateViewImage();
}

void MainWindow::on_action_symmetryHorizontalTransform_triggered()
{
    SymmetryTransform::transformHorizontal(&this->originalImage, &this->processImage);
    this->updateViewImage();
}

void MainWindow::on_action_symmetryVerticalTransform_triggered()
{
    SymmetryTransform::transformVertical(&this->originalImage, &this->processImage);
    this->updateViewImage();
}
