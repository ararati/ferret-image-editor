#ifndef EFFECTSWIDGET_H
#define EFFECTSWIDGET_H

#include <QWidget>
#include <mainwindow.h>

namespace Ui {
class EffectsWidget;
}

class EffectsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EffectsWidget(QWidget *parent = nullptr);
    ~EffectsWidget();

    void processViewType(QString type);
    void setMainWindow(MainWindow *mainWindow);
public slots:

private slots:
    void on_viewType_ComboBox_activated(const QString &arg1);

private:
    Ui::EffectsWidget *ui;
    MainWindow* mainWindow;
};

#endif // EFFECTSWIDGET_H
