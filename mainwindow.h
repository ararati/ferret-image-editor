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

    virtual bool eventFilter(QObject *obj, QEvent *event) override;
    void updateRgbStatus(int x, int y);
private slots:

    void on_brightnessSlider_valueChanged(int value);

    void on_viewTypeComboBox_currentTextChanged(const QString &arg1);

    void on_brightnessOk_btn_clicked();

    void saveProcessImage();
    void revertProcessImage();

    void on_contrastOk_btn_clicked();


    void on_contrastMin_spinBox_valueChanged(int arg1);

    void on_contrastMax_spinBox_valueChanged(int arg1);

    void on_contrastrgb_Slider_valueChanged(int value);

    void on_contrastrgbOk_btn_clicked();

    void on_discard_pushButton_clicked();

    void on_viewType_btn_clicked();

    void openFile();

    void on_actionOpenFile_triggered();

    void on_actionSaveFile_triggered();

    void on_actionSave_As_triggered();

    void on_actionInfoImage_triggered();

    void on_binarTreshold_Slider_valueChanged(int value);

    void on_action_TransformByHorizontal_triggered();

    void on_action_symmetryHorizontalTransform_triggered();

    void on_action_symmetryVerticalTransform_triggered();

private:
    Ui::MainWindow *ui;
    void displayImage(Image img, QLabel* source);
    Image originalImage;
    Image processImage;
    void contrastInputChanged();
    void processViewType(QString type);
    void loadImageByPath(string path);
    void saveFile();
    void saveFileAs();
};
#endif // MAINWINDOW_H
