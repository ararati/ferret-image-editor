#include "Helper.h"
#include "image.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include<QDebug>
#include "BrightnessCompute/BrightnessCorrection.h"
#include "ViewCompute/NegativeCompute.h"

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

    ui->label->setScaledContents(true);
    this->displayImage(this->processImage, ui->label);

    ui->viewTypeComboBox->addItem("Негатив");
    ui->viewTypeComboBox->addItem("Чёрно-белое");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateViewImage()
{
    this->displayImage(this->processImage, ui->label);
}

void MainWindow::displayImage(Image img, QLabel* source) {
    source->setPixmap(QPixmap::fromImage(img.toQImage()));
}

void MainWindow::on_brightnessSlider_valueChanged(int value)
{
    BrightnessCorrection::process(&this->originalImage, &this->processImage, value);

    this->updateViewImage();
}

void MainWindow::on_viewTypeButtonBox_accepted()
{
    QString choise = ui->viewTypeComboBox->currentText();
    this->processImage.getCvImg().copyTo(this->originalImage.getCvImg());
    qInfo() << choise;
}

void MainWindow::on_viewTypeComboBox_currentTextChanged(const QString &arg1)
{
    NegativeCompute::process(&this->originalImage, &this->processImage, 2);

    this->updateViewImage();
}
