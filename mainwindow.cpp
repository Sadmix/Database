#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->hide();
    auBox = new AuthorizationBox;
    connect(auBox, SIGNAL(sendData(QString, QString, QString)), this, SLOT(connectToDb(QString, QString, QString)));
    connect(auBox, SIGNAL(closeApp()), this, SLOT(close()));
    auBox->setWindowTitle("Authorization");
    auBox->show();
    db = QSqlDatabase::addDatabase("QMYSQL");
    query = new QSqlQuery;
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

    query->exec(data);
    updateTable();

}

void MainWindow::connectToDb(QString username, QString password, QString database){

    db.setHostName("127.0.0.1");
    db.setUserName("qtuser");
//    db.setUserName(username);
    db.setPassword("123");
    db.setPassword(password);
    db.setDatabaseName("test");
//    db.setDatabaseName("ElectronicsManufactoring");
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
    while(query->next()){
        for(int i = 0; i < query->record().count(); i++){
            QTableWidgetItem *item = new QTableWidgetItem(query->value(i).toString());
            ui->tableWidget->setItem(j, i, item);
        }
        j++;
    }

}

void MainWindow::on_tablesGBox_currentIndexChanged(const QString &arg1)
{
    currentTable = arg1;
    updateTable();
}
