#include "CoverImageDialog.h"
#include "ui_CoverImageDialog.h"

CoverImageDialog::CoverImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CoverImageDialog)
{
    ui->setupUi(this);
}

CoverImageDialog::~CoverImageDialog()
{
    delete ui;
}
