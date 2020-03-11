#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "image.h"
#include "qcustomplot.h"

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

    virtual bool eventFilter(QObject *obj, QEvent *event) override;
    void updateRgbStatus(int x, int y);
    void addImageTab(QString name);
    void setCommonSliderValue(int val);
    void updateHistogramEqualization();

    void displayImage(Image img, QLabel *source, bool scaling = false);
    void clearRedoUndoActions();
    void processColorBinary(int rPos, int gPos, int bPos);
    void toggleMask5x5();
    QString imageFileDialog();
    void processArithmeticOperation(QString arg1);
private slots:

    void on_brightnessSlider_valueChanged(int value);

    void on_viewTypeComboBox_currentTextChanged(const QString &arg1);

    void saveProcessImage();
    void revertProcessImage();

    void on_contrastMin_spinBox_valueChanged(int arg1);

    void on_contrastMax_spinBox_valueChanged(int arg1);

    void on_contrastrgb_Slider_valueChanged(int value);

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

    void on_action_TransformByVertical_triggered();

    void on_action_TransformAngleLeft_triggered();

    void on_action_TransformAngleRight_triggered();

    void on_actionNewFile_triggered();

    void on_imagesTabs_currentChanged(int index);

    void on_brightnessSlider_sliderReleased();

    void on_contrastrgb_Slider_sliderReleased();

    void on_contrastBW_okBtn_clicked();

    void on_action_equalizeHist_triggered();

    void on_action_normalizationImage_triggered();

    void plotDialogClosed();

    void on_action_averageBlur_triggered();

    void on_blurGausSlider_sliderReleased();

    void on_blurGausSlider_sliderMoved(int position);

    void on_blurGaus_saveBtn_clicked();

    void on_blurAverage_saveBtn_clicked();

    void on_blurAverage_Slider_sliderMoved(int position);

    void on_blurAverage_Slider_sliderReleased();

    void on_sharpMask_saveBtn_clicked();

    void on_masks_ComboBox_currentTextChanged(const QString &arg1);

    void on_blurGaus_apply_clicked();

    void on_sharpMask_applyBtn_clicked();

    void on_rndNoise_saveBtn_clicked();

    void on_whiteNoiseCount_Slider_sliderMoved(int position);

    void on_blackNoiseCount_Slider_sliderMoved(int position);

    void on_binarization_saveBtn_clicked();

    void on_commandLinkButton_medianSquare_clicked();

    void on_bioNoiseCount_Slider_sliderMoved(int position);

    void on_commandLinkButton_medianSquare_2_clicked();

    void on_btn_back_action_clicked();

    void on_btn_redo_action_clicked();

    void on_commandLinkButton_clicked();

    void on_btn_zoom_out_clicked();

    void on_btn_revert_processImage_clicked();

    void on_btn_medianCross_clicked();

    void on_btn_adaptiveMedianCross_clicked();

    void on_binarTresholdRed_Slider_sliderMoved(int position);

    void on_binarTresholdGreen_Slider_sliderMoved(int position);

    void on_binarTresholdBlue_Slider_sliderMoved(int position);

    void on_radioButton_mask5x5_clicked();

    void on_radioButton_mask3x3_clicked();

    void on_horizontalSlider_speedBlur_sliderReleased();


    void on_horizontalSlider_speedBlur_valueChanged(int value);

    void on_arithmeticImgLoad_pushButton_clicked();

    void on_arithmeticOperations_comboBox_currentTextChanged(const QString &arg1);

signals:
//    void plotDialogClosed();

private:
    Ui::MainWindow *ui;
    Image originalImage;
    Image processImage;

    Image coverOriginalImage;
    Image coverProcessImage;
    Image arithmeticImage;

    PlotDialog *plotDialog;
    bool plotDialogIsOpen = false;
    QStack<QImage> pastActions;
    QStack<QImage> redoActions;
    QPixmap viewImage;
    int originalImageWidth;
    int originalImageHeight;
    int imageViewWidth;
    int imageViewHeight;
    int scrollX = 0;
    float zoomFactor = 1;

    void contrastInputChanged();
    void processViewType(QString type);
    void loadImageByPath(QString path);
    void saveFile();
    void saveFileAs();
};
#endif // MAINWINDOW_H
