#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    context = allocateMemory();
    init();
    ui->setupUi(this);
    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::onOpenButtonClicked);
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);
    connect(ui->initButton, &QPushButton::clicked, this, &MainWindow::onInitButtonClicked);
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
    case NoDataInFile:
        QMessageBox::warning(this, "ERROR", "Нет данных в фвйле");
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
    if (context->fileOk)
        draw();
}

void MainWindow::onInitButtonClicked(){
    errorBox(entryPoint(Initialization, context));
    setInitParams();
}

void MainWindow::setInitParams(){
    ui->moveXLine->setText(QString::number(context->offsets.offsetX));
    ui->scaleLineX->setText(QString::number(context->scales.scaleX));
    ui->rolateXLine->setText(QString::number(context->radians.radiansX));
    ui->moveYLine->setText(QString::number(context->offsets.offsetY));
    ui->scaleLineY->setText(QString::number(context->scales.scaleY));
    ui->rolateYLine->setText(QString::number(context->radians.radiansY));
    ui->moveZLine->setText(QString::number(context->offsets.offsetZ));
    ui->scaleLineZ->setText(QString::number(context->scales.scaleZ));
    ui->rolateZLine->setText(QString::number(context->radians.radiansZ));
    ui->rangeMinLabel->setText(QString::number(context->range.downLimit));
    ui->rangeMaxLabel->setText(QString::number(context->range.upLimit));
}

void MainWindow::cleanMemory() {
    errorBox(entryPoint(Clean, context));
    free(context);
}

void MainWindow::draw() {
    QPixmap *pix = new QPixmap(780, 880);
    getGrafParams();
    drawGrafic(context, pix);
    ui->drawingLabel->setPixmap(*pix);
}

void MainWindow::getOffsetParams() {
    context->offsets.offsetX = ui->moveXLine->text().toInt();
    context->offsets.offsetY = ui->moveYLine->text().toInt();
    context->offsets.offsetZ = ui->moveZLine->text().toInt();
}

void MainWindow::getRolateParams() {
    context->radians.radiansX = ui->rolateXLine->text().toInt();
    context->radians.radiansY = ui->rolateYLine->text().toInt();
    context->radians.radiansZ = ui->rolateZLine->text().toInt();
}

void MainWindow::getScalesParams() {
   context->scales.scaleX = ui->scaleLineX->text().toInt();
   context->scales.scaleY = ui->scaleLineY->text().toInt();
   context->scales.scaleZ = ui->scaleLineZ->text().toInt();
}

void MainWindow::getRangeParams() {
    context->range.downLimit = ui->rangeMinLabel->text().toInt();
    context->range.upLimit = ui->rangeMaxLabel->text().toInt();
}

void MainWindow::getGrafParams() {
    getOffsetParams();
    getRolateParams();
    getScalesParams();
    getRangeParams();
}
