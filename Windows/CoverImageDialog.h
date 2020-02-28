#ifndef COVERIMAGEDIALOG_H
#define COVERIMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class CoverImageDialog;
}

class CoverImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CoverImageDialog(QWidget *parent = nullptr);
    ~CoverImageDialog();

private:
    Ui::CoverImageDialog *ui;
};

#endif // COVERIMAGEDIALOG_H
