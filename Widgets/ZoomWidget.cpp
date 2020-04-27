#include "ZoomWidget.h"
#include "ui_zoomwidget.h"

ZoomWidget::ZoomWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZoomWidget)
{
    ui->setupUi(this);

    maxZoomFactor = 7;
    step = 1.1;
}

ZoomWidget::~ZoomWidget()
{
    delete ui;
}

void ZoomWidget::setMainWindow(MainWindow* mainWindow) {
    this->mainWindow = mainWindow;
}

void ZoomWidget::on_commandLinkButton_clicked()
{
    if(mainWindow->getZoomFactor() < maxZoomFactor) {
        mainWindow->setZoomFactor(mainWindow->getZoomFactor() * 1.1f);
        mainWindow->updateViewImage(true);
    }

    ui->commandLinkButton->setDisabled(mainWindow->getZoomFactor() >= 7.f);
    ui->btn_zoom_out->setDisabled(mainWindow->getZoomFactor() == 1.f);
}

void ZoomWidget::on_btn_zoom_out_clicked()
{
    float factor = mainWindow->getZoomFactor();
    mainWindow->setZoomFactor((factor*0.1f <= 1) ? 1 : factor * 0.1f);

    mainWindow->updateViewImage(true);
    ui->btn_zoom_out->setDisabled(mainWindow->getZoomFactor() == 1.f);
    ui->commandLinkButton->setDisabled(mainWindow->getZoomFactor() >= 7);
}
