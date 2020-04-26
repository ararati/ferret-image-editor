#include "KernelWidget.h"
#include "ui_kernelwidget.h"

#include <ViewCompute/KernelFilters.h>
#include <ViewCompute/MaskFilter.h>

KernelWidget::KernelWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KernelWidget)
{
    ui->setupUi(this);

    QList<QString> filters;
    filters = {"Reset", "Average blur", "Sharpness", "Horizontal line", "Sobel: left border", "Sobel: right border", "Sobel: the upper bound", "Sobel: the lower bound"};

    foreach(QString type, filters) {
        ui->masks_ComboBox->addItem(type);
    }
}

KernelWidget::~KernelWidget()
{
    delete ui;
}

void KernelWidget::setMainWindow(MainWindow* mainWindow) {
    this->mainWindow = mainWindow;
}

void KernelWidget::on_masks_ComboBox_currentTextChanged(const QString &arg1)
{
    double mask[3][3];
    if(arg1 == "Sobel: left border")
        KernelFilters::leftSobel(mask);
    else if(arg1 == "Average blur")
        KernelFilters::smooth(mask);
    else if(arg1 == "Horizontal line")
        KernelFilters::horizontalLines(mask);
    else if(arg1 == "Sharpness")
        KernelFilters::sharpen(mask);
    else if(arg1 == "Sobel: right border")
        KernelFilters::rightSobel(mask);
    else if(arg1 == "Sobel: the lower bound")
        KernelFilters::bottomSobel(mask);
    else if(arg1 == "Sobel: the upper bound")
        KernelFilters::topSobel(mask);
    else KernelFilters::zeros(mask);

    ui->sharpMask00->setValue(mask[0][0]);
    ui->sharpMask10->setValue(mask[1][0]);
    ui->sharpMask20->setValue(mask[2][0]);

    ui->sharpMask01->setValue(mask[0][1]);
    ui->sharpMask11->setValue(mask[1][1]);
    ui->sharpMask12->setValue(mask[1][2]);

    ui->sharpMask02->setValue(mask[0][2]);
    ui->sharpMask21->setValue(mask[2][1]);
    ui->sharpMask22->setValue(mask[2][2]);
}

void KernelWidget::toggleMask5x5() {
    ui->sharpMask03->setEnabled(!ui->sharpMask03->isEnabled());
    ui->sharpMask04->setEnabled(!ui->sharpMask04->isEnabled());

    ui->sharpMask13->setEnabled(!ui->sharpMask13->isEnabled());
    ui->sharpMask14->setEnabled(!ui->sharpMask14->isEnabled());

    ui->sharpMask23->setEnabled(!ui->sharpMask23->isEnabled());
    ui->sharpMask24->setEnabled(!ui->sharpMask24->isEnabled());

    ui->sharpMask30->setEnabled(!ui->sharpMask30->isEnabled());
    ui->sharpMask31->setEnabled(!ui->sharpMask31->isEnabled());
    ui->sharpMask32->setEnabled(!ui->sharpMask32->isEnabled());
    ui->sharpMask33->setEnabled(!ui->sharpMask33->isEnabled());
    ui->sharpMask34->setEnabled(!ui->sharpMask34->isEnabled());

    ui->sharpMask40->setEnabled(!ui->sharpMask40->isEnabled());
    ui->sharpMask41->setEnabled(!ui->sharpMask41->isEnabled());
    ui->sharpMask42->setEnabled(!ui->sharpMask42->isEnabled());
    ui->sharpMask43->setEnabled(!ui->sharpMask43->isEnabled());
    ui->sharpMask44->setEnabled(!ui->sharpMask44->isEnabled());
}

void KernelWidget::on_radioButton_mask5x5_clicked()
{
    toggleMask5x5();
}

void KernelWidget::on_radioButton_mask3x3_clicked()
{
    toggleMask5x5();
}

void KernelWidget::on_sharpMask_applyBtn_clicked()
{
    int maskSize = (ui->radioButton_mask3x3->isChecked()) ? 3 : 5;

    float mask[31][31];

    mask[0][0] = ui->sharpMask00->value();
    mask[1][0] = ui->sharpMask10->value();
    mask[2][0] = ui->sharpMask20->value();

    mask[0][1] = ui->sharpMask01->value();
    mask[1][1] = ui->sharpMask11->value();
    mask[1][2] = ui->sharpMask12->value();

    mask[0][2] = ui->sharpMask02->value();
    mask[1][2] = ui->sharpMask12->value();
    mask[2][2] = ui->sharpMask22->value();

    if(maskSize == 5) {
        mask[0][3] = ui->sharpMask03->value();
        mask[0][4] = ui->sharpMask04->value();

        mask[1][3] = ui->sharpMask13->value();
        mask[1][4] = ui->sharpMask14->value();

        mask[2][3] = ui->sharpMask23->value();
        mask[2][4] = ui->sharpMask24->value();

        mask[3][0] = ui->sharpMask30->value();
        mask[3][1] = ui->sharpMask31->value();
        mask[3][2] = ui->sharpMask32->value();
        mask[3][3] = ui->sharpMask33->value();
        mask[3][4] = ui->sharpMask34->value();

        mask[4][0] = ui->sharpMask40->value();
        mask[4][1] = ui->sharpMask41->value();
        mask[4][2] = ui->sharpMask42->value();
        mask[4][3] = ui->sharpMask43->value();
        mask[4][4] = ui->sharpMask44->value();
    }

    MaskFilter::proccess(this->mainWindow->getOriginalImage(), this->mainWindow->getProcessImage(), maskSize, mask, ui->maskFactor_SpinBox->value(), ui->maskBias_SpinBox->value());

    this->mainWindow->updateViewImage();
}
