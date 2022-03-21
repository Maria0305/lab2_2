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
    QString regionName = ui->regionLineEdit->text();
    if (regionName == "" && context->fileName != NULL)
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
    ui->maxLabel->setText(QString::number(context->metrics.max, 'f', 2));
    ui->minLabel->setText(QString::number(context->metrics.min, 'f', 2));
    ui->mediumLabel->setText(QString::number(context->metrics.med, 'f', 2));
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
    case NoColumnChoosen:
        QMessageBox::warning(this, "ERROR", "Колонка не выбранa");
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
        context->dataForCalculating.fieldNum = ui->fieldLineEdit->text().toInt() - 1;
        if (context->dataForCalculating.fieldNum < context->columns && context->dataForCalculating.fieldNum > 1) {
            errorBox(getDataFromTable());
            errorBox(entryPoint(Calculate, context));
            drawGraf();
        }
        else
            if (ui->fieldLineEdit->text().isEmpty())
                errorBox(NoColumnChoosen);
            else
                errorBox(WrongColumnInput);
    }

}


bool checkNum(QString qstr){
    for( int i = 0; i < qstr.length(); i++)
        if (!qstr[i].isNumber())
            return false;
    return true;
}

ErrorType MainWindow::getDataFromTable(){
    float* values = (float*) malloc ( (ui->tableWidget->rowCount()) * sizeof(float));
    for (int i = 0; i < ui->tableWidget->rowCount(); i++){
            QTableWidgetItem* item = ui->tableWidget->item(i, context->dataForCalculating.fieldNum);
            values[i] = item->text().toFloat();
        }
    context->dataForCalculating.values = values;
    context->dataForCalculating.counter = ui->tableWidget->rowCount();
    return Correct;
}

void MainWindow::drawGraf(){
    QPixmap *pix = new QPixmap(780, 880);
    drawOrigins(context, pix);
    drawGrafic(context, pix);
    ui->drawingLabel->setPixmap(*pix);
}


void MainWindow::cleanMemory() {
    errorBox(entryPoint(Clean, context));
    free(context);
}

