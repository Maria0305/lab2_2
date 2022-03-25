#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    context = allocateMemory();
    init();
    ui->setupUi(this);
    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::onOpenButtonClicked);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);
}

MainWindow::~MainWindow(){
    cleanMemory();
    delete ui;
}

AppContext* MainWindow::allocateMemory(){
    return (AppContext*) malloc (sizeof(AppContext));
}

void MainWindow::onOpenButtonClicked(){
    init();
    QString fileName = QFileDialog::getOpenFileName(this, "Choose file", "C://", "CSV file (*.csv)");
    ui->fileLabel->setText(fileName);
    context->fileName = qstringToCharArray(fileName);
}

char* MainWindow::qstringToCharArray(QString qstr){
    char* str = (char*) malloc ((qstr.size() + 1) * sizeof(char));
    int i;
    for( i = 0; i < qstr.size(); i++)
        str[i] = qstr.at(i).unicode();
    str[i] = 0;
    return str;
}

void MainWindow::showData(){
    ui->tableWidget->setColumnCount(context->xSize);
    if (context->data != NULL) {
        ui->tableWidget->setRowCount(0);
        for (int i = 0; i < context->ySize; i++) {
            QStringList currentRow = convertRowToQStringList(context->data[i], context);
            ui->tableWidget->setRowCount(i + 1);
            for (int j = 0; j < context->xSize; j++) {
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setText(currentRow.at(j));
                ui->tableWidget->setItem(i, j, item);
            }
        }
    }
}


QStringList MainWindow::convertRowToQStringList(char** row, AppContext* context){
    QStringList qsl = {};
    for(int i = 0; i < context->xSize; i++) {
        qsl.append(QString::fromUtf8(row[i]));
    }
    return qsl;
}

void MainWindow::errorBox(ErrorType error){
    switch(error){
    case Unreadfile:
        QMessageBox::warning(this, "ERROR", "Невозможно прочитать файл");
        context->fileOk = false;
        break;
    case Nofilechoosen:
        QMessageBox::warning(this, "ERROR", "Файл не выбран");
        context->fileOk = false;
        break;
    case Correct:
        showData();
        break;
    default:
        break;
    }
}

void MainWindow::init(){
    errorBox(entryPoint(Initialization, context));
}

void MainWindow::onLoadButtonClicked(){
    context->fileOk = true;
    errorBox(entryPoint(Load, context));
}

bool checkNum(QString qstr){
    for( int i = 0; i < qstr.length(); i++)
        if (!qstr[i].isNumber())
            return false;
    return true;
}


void MainWindow::cleanMemory() {
    errorBox(entryPoint(Clean, context));
    free(context);
}

