#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include "entrypoint.h"
#include "drawing.h"
#include "appcontext.h"
#include "entrypoint.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AppContext* context;
    AppContext* allocateMemory();
    QStringList convertRowToQStringList(char**, AppContext*);
    char* qstringToCharArray(QString);
    void onOpenButtonClicked();
    void onLoadButtonClicked();
    void onCalculateButtonClicked();
    ErrorType getDataFromTable();
    void drawGraf();
    void errorBox(ErrorType);
    void init();
    void cleanMemory();
    void showData();
    void showMetrics();
    bool checkNum(QString);
};
#endif // MAINWINDOW_H
