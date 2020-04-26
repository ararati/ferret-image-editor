#ifndef KERNELWIDGET_H
#define KERNELWIDGET_H

#include <QWidget>
#include <mainwindow.h>

namespace Ui {
class KernelWidget;
}

class KernelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit KernelWidget(QWidget *parent = nullptr);
    ~KernelWidget();

    void setMainWindow(MainWindow *mainWindow);
private slots:
    void on_masks_ComboBox_currentTextChanged(const QString &arg1);

    void on_radioButton_mask3x3_clicked();

    void on_radioButton_mask5x5_clicked();

    void on_sharpMask_applyBtn_clicked();

private:
    MainWindow* mainWindow;
    Ui::KernelWidget *ui;
    void toggleMask5x5();
};

#endif // KERNELWIDGET_H
