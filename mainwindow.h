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
    char* qstringToCharArray(QString);
    void onOpenButtonClicked();
    void onLoadButtonClicked();
    void onInitButtonClicked();
    void setInitParams();
    void getGrafParams();
    void getOffsetParams();
    void getRolateParams();
    void getScalesParams();
    void getRangeParams();
    void errorBox(ErrorType);
    void init();
    void cleanMemory();
    void draw();
};
#endif // MAINWINDOW_H
