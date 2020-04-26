#ifndef ARITHMETICWIDGET_H
#define ARITHMETICWIDGET_H

#include <QWidget>
#include <mainwindow.h>

namespace Ui {
class ArithmeticWidget;
}

class ArithmeticWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArithmeticWidget(QWidget *parent = nullptr);
    ~ArithmeticWidget();

    void setMainWindow(MainWindow *mainWindow);
    void processArithmeticOperation(QString arg1);
public slots:
    void on_arithmeticImgLoad_pushButton_clicked();
private slots:
    void on_arithmeticOperation_comboBox_activated(const QString &arg1);

private:
    Image arithmeticImage;
    MainWindow* mainWindow;
    Ui::ArithmeticWidget *ui;
};

#endif // ARITHMETICWIDGET_H
