#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "entrypoint.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    context = allocateMemory();
    init();
    ui->setupUi(this);
    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::onOpenButtonClicked);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);
    connect(ui->calculateButton, &QPushButton::clicked, this, &MainWindow::onCalculateButtonClicked);
}

MainWindow::~MainWindow(){
    cleanMemory();
    delete ui;
}

AppContext* MainWindow::allocateMemory(){
    return (AppContext*) malloc (sizeof(AppContext));
}

void MainWindow::onOpenButtonClicked(){
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
    QString regionName = ui->regionLineEdit->text();
    if (regionName == "")
        errorBox(NoRegionChoosen);
    ui->tableWidget->setColumnCount(context->columns);
    QStringList qColumns = convertRowToQStringList(context->titles, context);
    ui->tableWidget->setHorizontalHeaderLabels(qColumns);
    if (context->data != NULL) {
        ui->tableWidget->setRowCount(0);
        int k = 0;
        for (int i = 0; i < context->rows; i++) {
            QStringList currentRow = convertRowToQStringList(context->data[i], context);
            if (regionName == currentRow.at(1)) {
                ui->tableWidget->setRowCount(k + 1);
                for (int j = 0; j < context->columns; j++) {
                    QTableWidgetItem* item = new QTableWidgetItem();
                    item->setText(currentRow.at(j));
                    ui->tableWidget->setItem(k, j, item);
                }
                k++;
            }
        }
    }
}

void MainWindow::showMetrics(){
    ui->maxLabel->setText(QString::number(context->max, 'f', 2));
    ui->minLabel->setText(QString::number(context->min, 'f', 2));
    ui->mediumLabel->setText(QString::number(context->med, 'f', 2));
}

QStringList MainWindow::convertRowToQStringList(char** row, AppContext* context){
    QStringList qsl = {};
    for(int i = 0; i < context->columns; i++) {
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
    case WrongColumnInput:
        QMessageBox::warning(this, "ERROR", "Неправильный ввод номера колонки");
        break;
    case Nofilechoosen:
        QMessageBox::warning(this, "ERROR", "Файл не выбран");
        context->fileOk = false;
        break;
    case NoRegionChoosen:
        QMessageBox::warning(this, "ERROR", "Регион не выбран");
        break;
    case NoDataForThisRegion:
        QMessageBox::warning(this, "ERROR", "Нет данных для выбранного региона");
        context->fileOk = false;
        break;
    case Correct:
        showData();
        showMetrics();
        break;
    default:
        break;
    }
}

void MainWindow::init(){
    errorBox(entryPoint(Initialization, context));
    errorBox(entryPoint(Metrics, context));
}

void MainWindow::onLoadButtonClicked(){
    context->fileOk = true;
    errorBox(entryPoint(Load, context));
}

void MainWindow::onCalculateButtonClicked(){
    errorBox(entryPoint(Metrics, context));
    onLoadButtonClicked();
    if (context->fileOk) {
        context->fieldNum = ui->fieldLineEdit->text().toInt() - 1;
        if (context->fieldNum < context->columns && context->fieldNum > 1) {
            float* values = (float*) malloc ( (ui->tableWidget->rowCount()) * sizeof(float));
            for (int i = 0; i < ui->tableWidget->rowCount(); i++){
                    QTableWidgetItem* item = ui->tableWidget->item(i, context->fieldNum);
                    values[i] = item->text().toFloat();
                }
            context->values = values;
            context->counter = ui->tableWidget->rowCount();
            errorBox(entryPoint(Calculate, context));
        }
        else
            errorBox(WrongColumnInput);
    }
}

void MainWindow::cleanMemory() {
    errorBox(entryPoint(Clean, context));
    free(context);
}
