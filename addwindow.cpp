#include "addwindow.h"

AddWindow::AddWindow(QWidget *parent, QStringList rowNames, QStringList rowTypes) : QWidget(parent)
{
    mainLayout = new QGridLayout();
    acceptBtn = new QPushButton();
    cancelBtn = new QPushButton();

    setWindowTitle("Add data");
    acceptBtn->setText("Accept");
    cancelBtn->setText("Cancel");

    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));
    connect(acceptBtn, SIGNAL(clicked()), this, SLOT(onAcceptBtnClicked()));

    this->rowNames = rowNames;
    this->rowTypes = rowTypes;
    setLayout(mainLayout);
    for(int i = 0; i < rowNames.size(); i++){

        mainLayout->addWidget(new QLabel(rowNames[i]), i, 0);

        if (QRegExp("\\b(date)\\b").indexIn(rowTypes[i]) > -1)
        {
            MyDateEdit *dataField = new MyDateEdit();
            dataFields.push_back(dataField);
            mainLayout->addWidget(dataField, i, 1);

        } else {
            MyLineEdit *dataField = new MyLineEdit();
            dataFields.push_back(dataField);
            if(QRegExp("\\b(int)\\b").indexIn(rowTypes[i]) > -1){
                dataField->setValidator(new QIntValidator(INT_MIN, INT_MAX, this));
            }
            mainLayout->addWidget(dataField, i, 1);
        }
        dataList.append("");
    }

    mainLayout->addWidget(cancelBtn, rowNames.size(), 0);
    mainLayout->addWidget(acceptBtn, rowNames.size(), 1);

    for(auto dataField : dataFields){
        connect(dataField, SIGNAL(dataChanged(QWidget*, QString)), this, SLOT(onUpdateData(QWidget*, QString)));
    }

}

void AddWindow::onAcceptBtnClicked(){

    QString data;
    data.append("(");

    for(int i = 0; i < dataList.size(); i++){

        if(QRegExp("\\b(int)\\b").indexIn(rowTypes[i]) > -1){
            data.append(dataList[i]+",");
        } else {
            data.append("'" + dataList[i] + "',");
        }

    }

    data.replace(data.size()-1, 1, ")");

    emit writeData(data);
    close();

}

void AddWindow::onUpdateData(QWidget* obj, QString data){

    dataList[(dataFields.indexOf(obj))] = data;

}

void AddWindow::onCancelBtnClicked(){

    close();

}
