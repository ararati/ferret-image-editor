#include "ArithmeticWidget.h"
#include "ui_arithmeticwidget.h"
#include "ViewCompute/ArithmeticOperations.h"

ArithmeticWidget::ArithmeticWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArithmeticWidget)
{
    ui->setupUi(this);

    QList<QString> arithmeticOperations;
    arithmeticOperations = {"Sum", "Difference", "Multiplication", "Average", "Min", "Max", "OR", "AND", "XOR"};

    foreach(QString op, arithmeticOperations) {
        ui->arithmeticOperation_comboBox->addItem(op);
    }
}

ArithmeticWidget::~ArithmeticWidget()
{
    delete ui;
}

void ArithmeticWidget::setMainWindow(MainWindow* mainWindow) {
    this->mainWindow = mainWindow;
}


void ArithmeticWidget::on_arithmeticImgLoad_pushButton_clicked()
{
    this->mainWindow->revertProcessImage();

    QString path = this->mainWindow->imageFileDialog();
    if(path == "") return;

    //TODO: For refactoring
    if(ui->aritmeticImgSize_checkBox->isChecked()) {
        arithmeticImage = Image(*mainWindow->getOriginalImage());
        QImage img = QImage(path);
        img = img.scaled(mainWindow->getOriginalImage()->width(), mainWindow->getOriginalImage()->height());
        arithmeticImage.copyFrom(&img);
    } else arithmeticImage = Image(path);

    QPixmap pix = QPixmap::fromImage(arithmeticImage).scaled(ui->arithmeticImg_label->width(),ui->arithmeticImg_label->height(),Qt::KeepAspectRatio);

    ui->arithmeticImg_label->setPixmap(pix);

    processArithmeticOperation(ui->arithmeticOperation_comboBox->currentText());

    this->mainWindow->updateViewImage();
}

void ArithmeticWidget::processArithmeticOperation(QString arg1) {
    if(arg1 == "Sum")
        ArithmeticOperations::sum(mainWindow->getOriginalImage(), mainWindow->getProcessImage(), &arithmeticImage);
    else if(arg1 == "Difference")
        ArithmeticOperations::diff(mainWindow->getOriginalImage(), mainWindow->getProcessImage(), &arithmeticImage);
    else if(arg1 == "Multiplication")
        ArithmeticOperations::mul(mainWindow->getOriginalImage(), mainWindow->getProcessImage(), &arithmeticImage);
    else if(arg1 == "Average")
        ArithmeticOperations::average(mainWindow->getOriginalImage(), mainWindow->getProcessImage(), &arithmeticImage);
    else if(arg1 == "Min")
        ArithmeticOperations::min(mainWindow->getOriginalImage(), mainWindow->getProcessImage(), &arithmeticImage);
    else if(arg1 == "Max")
        ArithmeticOperations::max(mainWindow->getOriginalImage(), mainWindow->getProcessImage(), &arithmeticImage);
    else if(arg1 == "OR")
        ArithmeticOperations::OR(mainWindow->getOriginalImage(), mainWindow->getProcessImage(), &arithmeticImage);
    else if(arg1 == "AND")
        ArithmeticOperations::AND(mainWindow->getOriginalImage(), mainWindow->getProcessImage(), &arithmeticImage);
    else if(arg1 == "XOR")
        ArithmeticOperations::XOR(mainWindow->getOriginalImage(), mainWindow->getProcessImage(), &arithmeticImage);
}

void ArithmeticWidget::on_arithmeticOperation_comboBox_activated(const QString &arg1)
{
    processArithmeticOperation(arg1);

    this->mainWindow->updateViewImage();
}
