#include "PlotDialog.h"
#include "ui_PlotDialog.h"

#include <ViewCompute/HistogramEqualization.h>

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

void PlotDialog::updatePlot(Image* proccessingImage, Image* savedImage) {
    QVector<double> x(256);
    for(int i =  0; i < 256; i++) {
        x[i] = i;
    }
    QVector<double> y = HistogramEqualization::bwBrightnessData(proccessingImage);
    QVector<double> y2 = HistogramEqualization::bwBrightnessData(savedImage);

    double maxY = *std::max_element(y.constBegin(), y.constEnd());
    double maxY2 = *std::max_element(y2.constBegin(), y2.constEnd());
    maxY = max(maxY, maxY2);

    QCustomPlot* plot = getPlot();

    plot->legend->setVisible(true);
    plot->addGraph();
    plot->graph(0)->setPen(QPen(QColor(0, 0, 255)));
    plot->graph(0)->setName("Processing");
    plot->addGraph();
    plot->graph(1)->setPen(QPen(QColor(255, 0, 0)));
    plot->graph(1)->setName("Saved");

    plot->xAxis->setLabel("brightness");
    plot->yAxis->setLabel("intensity");

    plot->xAxis->setRange(0, 255);
    plot->yAxis->setRange(0, maxY);

    plot->graph(0)->setData(x, y);
    plot->graph(1)->setData(x, y2);
    plot->replot();
    plot->clearPlottables();
}
