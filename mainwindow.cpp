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
    entryPoint(Initialization, context);
    QString fileName = QFileDialog::getOpenFileName(this, "Choose file", "C://", "CSV file (*.csv)");
    if (fileName != "") {
        context->fileName = qstringToCharArray(fileName);
        ui->fileLabel->setText(context->fileName);
    }
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
        break;
    case Nofilechoosen:
        QMessageBox::warning(this, "ERROR", "Файл не выбран");
        break;
    case NoDataInFile:
        QMessageBox::warning(this, "ERROR", "Нет данных в файле");
        break;
    default:
        break;
    }
}

void MainWindow::init(){
    context->fileName = NULL;
    errorBox(entryPoint(Initialization, context));
}

void MainWindow::onLoadButtonClicked(){
    ErrorType fileNeOk = entryPoint(Load, context);
    if (fileNeOk == Unreadfile || fileNeOk == Nofilechoosen) {
        errorBox(fileNeOk);
        return;
    }
    draw();
}

void MainWindow::onInitButtonClicked(){
    errorBox(entryPoint(Initialization, context));
    setInitParams();
    onLoadButtonClicked();
}

void MainWindow::setInitParams(){
    ui->moveXLine->setText(QString::number(context->offsets.x));
    ui->scaleLineX->setText(QString::number(context->scales.x));
    ui->rolateXLine->setText(QString::number(context->radians.x));
    ui->moveYLine->setText(QString::number(context->offsets.y));
    ui->scaleLineY->setText(QString::number(context->scales.y));
    ui->rolateYLine->setText(QString::number(context->radians.y));
    ui->moveZLine->setText(QString::number(context->offsets.z));
    ui->scaleLineZ->setText(QString::number(context->scales.z));
    ui->rolateZLine->setText(QString::number(context->radians.z));
    ui->rangeMinLabel->setText(QString::number(context->range.to));
    ui->rangeMaxLabel->setText(QString::number(context->range.from));
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
    context->offsets.x = ui->moveXLine->text().toInt();
    context->offsets.y = ui->moveYLine->text().toInt();
    context->offsets.z = ui->moveZLine->text().toInt();
}

void MainWindow::getRolateParams() {
    context->radians.x = ui->rolateXLine->text().toInt();
    context->radians.y = ui->rolateYLine->text().toInt();
    context->radians.z = ui->rolateZLine->text().toInt();
}

void MainWindow::getScalesParams() {
   context->scales.x = ui->scaleLineX->text().toInt();
   context->scales.y = ui->scaleLineY->text().toInt();
   context->scales.z = ui->scaleLineZ->text().toInt();
}

void MainWindow::getRangeParams() {
    context->range.to = ui->rangeMinLabel->text().toInt();
    context->range.from = ui->rangeMaxLabel->text().toInt();
}

void MainWindow::getGrafParams() {
    getOffsetParams();
    getRolateParams();
    getScalesParams();
    getRangeParams();
}
