#include "EffectsWidget.h"
#include "ui_effectswidget.h"

#include "ViewCompute/SingleColorView.h"
#include "ViewCompute/NegativeView.h"
#include "ViewCompute/GrayscaleView.h"

EffectsWidget::EffectsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EffectsWidget)
{
    ui->setupUi(this);

    QList<QString> viewType;
    viewType = {"Normal", "Negative", "Black and White", "Red", "Green", "Blue"};
    foreach(QString type, viewType) {
        ui->viewType_ComboBox->addItem(type);
    }
}

EffectsWidget::~EffectsWidget()
{
    delete ui;
}

void EffectsWidget::setMainWindow(MainWindow* mainWindow) {
    this->mainWindow = mainWindow;
}

void EffectsWidget::processViewType(QString type) {

    if(type == "Normal") {
        mainWindow->revertProcessImage();
    } else if(type == "Negative") {
        NegativeView::process(mainWindow->getOriginalImage(), mainWindow->getProcessImage());
    } else if(type == "Black and White") {
        GrayscaleView::process(mainWindow->getOriginalImage(), mainWindow->getProcessImage());
    } else if(type == "Red") {
        SingleColorView::process(mainWindow->getOriginalImage(), mainWindow->getProcessImage(), 0);
    } else if(type == "Green") {
        SingleColorView::process(mainWindow->getOriginalImage(), mainWindow->getProcessImage(), 1);
    } else if(type == "Blue") {
        SingleColorView::process(mainWindow->getOriginalImage(), mainWindow->getProcessImage(), 2);
    }
}

void EffectsWidget::on_viewType_ComboBox_activated(const QString &arg1)
{
    this->processViewType(arg1);
    mainWindow->updateViewImage();
}
