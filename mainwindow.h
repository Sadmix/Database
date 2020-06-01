#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QMessageBox>
#include <QString>

#include "authorizationbox.h"
#include "addwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void addToDb(QString data);
    void connectToDb(QString username, QString password, QString database);
    void updateTablesGBox(QStringList tables);
    void updateTable();

    void on_tablesGBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    AuthorizationBox *auBox;
    QSqlQuery *query;
    QString currentTable;
};
#endif // MAINWINDOW_H
