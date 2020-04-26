#ifndef UNDOREDOACTIONSWIDGET_H
#define UNDOREDOACTIONSWIDGET_H

#include <QWidget>
#include <mainwindow.h>

namespace Ui {
class UndoRedoActionsWidget;
}

class UndoRedoActionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UndoRedoActionsWidget(QWidget *parent = nullptr);
    ~UndoRedoActionsWidget();

    void setMainWindow(MainWindow *mainWindow);
    void addToHistory(Image obj);
    QStack<QImage> getPastActions();
    QStack<QImage> getRedoActions();
    void clearRedoUndoActions();
public slots:
    void on_btn_back_action_clicked();
    void on_btn_redo_action_clicked();
private:
    Ui::UndoRedoActionsWidget *ui;
    MainWindow* mainWindow;
    QStack<QImage> pastActions;
    QStack<QImage> redoActions;
};

#endif // UNDOREDOACTIONSWIDGET_H
