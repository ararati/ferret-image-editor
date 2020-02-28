#include "PlotDialog.h"
#include "ui_PlotDialog.h"

PlotDialog::PlotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotDialog)
{
    ui->setupUi(this);

//    ui->plotWidget->setInteraction(QCP::iRangeDrag, true);
//    ui->plotWidget->setInteraction(QCP::iRangeZoom, true);
}

PlotDialog::~PlotDialog()
{
    delete ui;
}

QCustomPlot *PlotDialog::getPlot() {
    return ui->plotWidget;
}
