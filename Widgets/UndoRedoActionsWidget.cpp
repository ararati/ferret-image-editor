#include "UndoRedoActionsWidget.h"
#include "ui_undoRedoActionsWidget.h"

UndoRedoActionsWidget::UndoRedoActionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UndoRedoActionsWidget)
{
    ui->setupUi(this);
}

UndoRedoActionsWidget::~UndoRedoActionsWidget()
{
    delete ui;
}

void UndoRedoActionsWidget::setMainWindow(MainWindow* mainWindow) {
    this->mainWindow = mainWindow;
}

void UndoRedoActionsWidget::addToHistory(Image obj) {
    pastActions.push(obj);

    qInfo() << (pastActions.count() == 0);
    ui->btn_back_action->setDisabled(pastActions.count() == 0);
    ui->btn_redo_action->setDisabled(redoActions.count() == 0);
}

QStack<QImage> UndoRedoActionsWidget::getPastActions() {
    return pastActions;
}

QStack<QImage> UndoRedoActionsWidget::getRedoActions() {
    return redoActions;
}

void UndoRedoActionsWidget::clearRedoUndoActions() {
    redoActions.clear();
    pastActions.clear();
    ui->btn_back_action->setDisabled(pastActions.count() == 0);
    ui->btn_redo_action->setDisabled(redoActions.count() == 0);
}

void UndoRedoActionsWidget::on_btn_back_action_clicked()
{
    redoActions.clear();
    redoActions.push(*mainWindow->getOriginalImage());

    QImage img = pastActions.pop();

    mainWindow->getProcessImage()->copyFrom(&img);
    mainWindow->getOriginalImage()->copyFrom(mainWindow->getProcessImage());
    mainWindow->updateViewImage();

    ui->btn_back_action->setDisabled(pastActions.count() == 0);
    ui->btn_redo_action->setDisabled(redoActions.count() == 0);
}

void UndoRedoActionsWidget::on_btn_redo_action_clicked()
{
    QImage img = redoActions.pop();

    pastActions.push(*mainWindow->getOriginalImage());
    mainWindow->getProcessImage()->copyFrom(&img);
    mainWindow->getOriginalImage()->copyFrom(mainWindow->getProcessImage());
    mainWindow->updateViewImage();

    ui->btn_back_action->setDisabled(pastActions.count() == 0);
    ui->btn_redo_action->setDisabled(redoActions.count() == 0);
}
