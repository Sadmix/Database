#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auBox = new AuthorizationBox;
    connect(auBox, SIGNAL(sendData(QString, QString, QString)), this, SLOT(connectToDb(QString, QString, QString)));
    connect(auBox, SIGNAL(closeApp()), this, SLOT(close()));
    auBox->setWindowTitle("Authorization");
    auBox->show();
    db = QSqlDatabase::addDatabase("QMYSQL");
    query = new QSqlQuery;
    currentItem = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    AddWindow *addWindow = new AddWindow(nullptr, currentTable);
    connect(addWindow, SIGNAL(writeData(QString)), this, SLOT(addToDb(QString)));
    addWindow->show();
}

void MainWindow::addToDb(QString data){

    if(query->exec(data)){

        updateTable();

    }else{

        QMessageBox::information(this, "Error", query->lastError().text());

    }

}

void MainWindow::connectToDb(QString username, QString password, QString database){

    db.setHostName("127.0.0.1");
    db.setUserName("qtuser");
//    db.setUserName(username);
    db.setPassword("123");
//    db.setPassword(password);
//    db.setDatabaseName("test");
    db.setDatabaseName("ElectronicsManufactoring");
//    db.setDatabaseName(database);
    if(db.open()){
        qDebug() << "Connected to DB";
        this->show();
        auBox->close();
    } else {
        qDebug() << " Not connected to DB";
        QMessageBox::information(auBox, "Error", "Wrong login or password!");
    }

    query->exec("SHOW TABLES");
    QStringList tables;
    while(query->next()){
        tables.append(query->value(0).toString());
    }
    updateTablesGBox(tables);

}

void MainWindow::updateTablesGBox(QStringList tables){
    ui->tablesGBox->addItems(tables);
}

void MainWindow::updateTable(){

    query->exec("DESC " + currentTable);
    QStringList headers;
    while(query->next()){
        headers.append(query->value(0).toString());
    }
    query->exec("SELECT * FROM " + currentTable);
    ui->tableWidget->setColumnCount(query->record().count());
    ui->tableWidget->setRowCount(query->size());
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    int j = 0;
    headers.clear();
    while(query->next()){
        for(int i = 0; i < query->record().count(); i++){
            QTableWidgetItem *item = new QTableWidgetItem(query->value(i).toString());
            ui->tableWidget->setItem(j, i, item);
        }
        j++;
        headers.append("");
    }
    ui->tableWidget->setVerticalHeaderLabels(headers);
    ui->tableWidget->verticalHeader()->setMinimumSize(10,10);

}

void MainWindow::on_tablesGBox_currentIndexChanged(const QString &arg1)
{
    currentTable = arg1;
    updateTable();
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    if(currentItem == item){

        int row = item->row();
        int column = item->column();
        QString columnName = ui->tableWidget->horizontalHeaderItem(column)->text();
        QString newValue = "'" + ui->tableWidget->item(row, column)->text() + "'";
        QString keyName;
        int pos = 0;
        query->exec("DESC " + currentTable);
        while(query->next()){
            if(QRegExp("\\b(PRI)\\b").indexIn(query->value(3).toString()) >= 0){

                keyName = query->value(0).toString();
                break;

            }
            pos++;
        }

        QString keyValue = ui->tableWidget->item(row, pos)->text();
        query->exec("UPDATE " + currentTable + " SET " + columnName + " = " + newValue + " WHERE " + keyName + " = " + keyValue);
    }
}

void MainWindow::on_tableWidget_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    currentItem = current;
}

void MainWindow::on_pushButton_2_clicked()
{
    if(currentItem == nullptr){
        return;
    }
    int row = currentItem->row();
    QString keyName;
        int pos = 0;
        query->exec("DESC " + currentTable);
        while(query->next()){
            if(QRegExp("\\b(PRI)\\b").indexIn(query->value(3).toString()) >= 0){

                keyName = query->value(0).toString();
                break;

            }
            pos++;
        }

        QString keyValue = ui->tableWidget->item(row, pos)->text();
        query->exec("DELETE FROM " + currentTable + " WHERE " + keyName + " = " + keyValue);
        updateTable();
        currentItem = nullptr;
}
