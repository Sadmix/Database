#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QWidget>
#include <QStringList>
#include <QLabel>
#include <QGridLayout>
#include <QList>
#include <QPushButton>
#include <QValidator>
#include <QDateEdit>
#include <QSqlQuery>

#include <QDebug>

#include "mylineedit.h"
#include "mydateedit.h"

class AddWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AddWindow(QWidget *parent = nullptr, QString currentTable = "");

signals:

    void writeData(QString data);

private slots:

    void onCancelBtnClicked();
    void onAcceptBtnClicked();
    void onUpdateData(QWidget* obj, QString data);

private:
    QStringList rowNames;
    QStringList rowTypes;
    QList<bool> rowAutoIncrement;
    QStringList dataList;
    QGridLayout *mainLayout;
    QList<QWidget*> dataFields;
    QPushButton *cancelBtn;
    QPushButton *acceptBtn;

    QString currentTable;

};

#endif // ADDWINDOW_H
