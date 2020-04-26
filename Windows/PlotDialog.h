#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <Image.h>
#include <QDialog>
#include <Widgets/qcustomplot.h>

namespace Ui {
class PlotDialog;
}

class PlotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotDialog(QWidget *parent = nullptr);
    ~PlotDialog();

    QCustomPlot *getPlot();
    void updatePlot(Image *proccessingImage, Image *savedImage);
private:
    Ui::PlotDialog *ui;
};

#endif // PLOTDIALOG_H
