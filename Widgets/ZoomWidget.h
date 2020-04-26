#ifndef ZOOMWIDGET_H
#define ZOOMWIDGET_H

#include <QWidget>
#include <mainwindow.h>

namespace Ui {
class ZoomWidget;
}

class ZoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ZoomWidget(QWidget *parent = nullptr);
    ~ZoomWidget();

    void setMainWindow(MainWindow *mainWindow);
public slots:
    void on_commandLinkButton_clicked();
    void on_btn_zoom_out_clicked();
private:
    Ui::ZoomWidget *ui;
    MainWindow* mainWindow;
};

#endif // ZOOMWIDGET_H
