#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Image.h"
#include "Widgets/qcustomplot.h"

#include <QLabel>
#include <QMainWindow>

#include <Windows/PlotDialog.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateViewImage(bool updateGeometry=true);

    void setCommonSliderValue(int val);
    void updateHistogramEqualization();

    void displayImage(Image img, QLabel *source, bool scaling = false);
    void processColorBinary(int rPos, int gPos, int bPos);
    void toggleMask5x5();
    QString imageFileDialog();
    Image* getOriginalImage();
    Image* getProcessImage();
    void saveProcessImage();
    void revertProcessImage();

    void applyProcessImage();
    float getZoomFactor();
    float setZoomFactor(float fact);
    QImage scaleImage(QImage *img);
    int getViewContainerHeight();
    int getViewContainerWidth();
private slots:

    void on_brightnessSlider_valueChanged(int value);

    void on_contrastMin_spinBox_valueChanged(int arg1);

    void on_contrastMax_spinBox_valueChanged(int arg1);

    void on_contrastrgb_Slider_valueChanged(int value);

    void openFile();

    void on_actionOpenFile_triggered();

    void on_actionSaveFile_triggered();

    void on_actionSave_As_triggered();

    void on_actionInfoImage_triggered();

    void on_binarTreshold_Slider_valueChanged(int value);

    void on_action_TransformByHorizontal_triggered();

    void on_action_symmetryHorizontalTransform_triggered();

    void on_action_symmetryVerticalTransform_triggered();

    void on_action_TransformByVertical_triggered();

    void on_action_TransformAngleLeft_triggered();

    void on_action_TransformAngleRight_triggered();

    void on_action_equalizeHist_triggered();

    void on_action_normalizationImage_triggered();

    void plotDialogClosed();

    void on_blurGausSlider_sliderMoved(int position);

    void on_blurAverage_Slider_sliderMoved(int position);

    void on_blurAverage_Slider_sliderReleased();

    void on_blurGaus_apply_clicked();

    void on_whiteNoiseCount_Slider_sliderMoved(int position);

    void on_blackNoiseCount_Slider_sliderMoved(int position);

    void on_commandLinkButton_medianSquare_clicked();

    void on_bioNoiseCount_Slider_sliderMoved(int position);

    void on_commandLinkButton_medianSquare_2_clicked();

    void on_btn_revert_processImage_clicked();

    void on_btn_medianCross_clicked();

    void on_btn_adaptiveMedianCross_clicked();

    void on_binarTresholdRed_Slider_sliderMoved(int position);

    void on_binarTresholdGreen_Slider_sliderMoved(int position);

    void on_binarTresholdBlue_Slider_sliderMoved(int position);

    void on_horizontalSlider_speedBlur_sliderReleased();

    void on_horizontalSlider_speedBlur_valueChanged(int value);

    void on_commandLinkButton_dilate_clicked();

    void on_commandLinkButton_erosion_clicked();

    void on_actionAbout_triggered();

    void resizeEvent(QResizeEvent *event);
    void on_applyChanges_btn_clicked();

signals:


private:
    Ui::MainWindow *ui;
    Image originalImage;
    Image processImage;

    PlotDialog *plotDialog;
    QPixmap viewImage;

    bool plotDialogIsOpen = false;
    float zoomFactor = 1.f;

    int viewContainerHeight = 0;
    int viewContainerWidth = 0;

    void contrastInputChanged();
    void processViewType(QString type);
    void loadImageByPath(QString path);
    void saveFile();
    void saveFileAs();
    void setStyleSheet();
    void setInitialImage();
    void setViewContainerHeight(int arg);
    void setViewContainerWidth(int arg);
};
#endif // MAINWINDOW_H
