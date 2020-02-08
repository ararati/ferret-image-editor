#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "image.h"

#include <QLabel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateViewImage();

private slots:

    void on_brightnessSlider_valueChanged(int value);

    void on_viewTypeButtonBox_accepted();

    void on_viewTypeComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    void displayImage(Image img, QLabel* source);
    Image originalImage;
    Image processImage;
};
#endif // MAINWINDOW_H
