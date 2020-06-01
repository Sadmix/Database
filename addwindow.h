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

#include <QDebug>

#include "mylineedit.h"
#include "mydateedit.h"

class AddWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AddWindow(QWidget *parent = nullptr, QStringList rowNames = {""}, QStringList rowTypes = {""});

signals:

    void writeData(QString data);

private slots:

    void onCancelBtnClicked();
    void onAcceptBtnClicked();
    void onUpdateData(QWidget* obj, QString data);

private:
    QStringList rowNames;
    QStringList rowTypes;
    QStringList dataList;
    QGridLayout *mainLayout;
    QList<QWidget*> dataFields;
    QPushButton *cancelBtn;
    QPushButton *acceptBtn;

};

#endif // ADDWINDOW_H
