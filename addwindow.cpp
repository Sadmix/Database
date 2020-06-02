#include "addwindow.h"

AddWindow::AddWindow(QWidget *parent, QString currentTable) : QWidget(parent)
{
    this->currentTable = currentTable;
    QSqlQuery query;
    query.exec("DESC " + currentTable);
    while(query.next()){
        rowNames.append(query.value(0).toString());
        rowTypes.append(query.value(1).toString());
        rowAutoIncrement.append(QRegExp("\\b(auto_increment\\b)").indexIn(query.value(5).toString()) >= 0);
    }

    mainLayout = new QGridLayout();
    acceptBtn = new QPushButton();
    cancelBtn = new QPushButton();

    setWindowTitle("Add data");
    acceptBtn->setText("Accept");
    cancelBtn->setText("Cancel");

    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));
    connect(acceptBtn, SIGNAL(clicked()), this, SLOT(onAcceptBtnClicked()));

    setLayout(mainLayout);
    for(int i = 0; i < rowNames.size(); i++){

        if(rowAutoIncrement[i]){
            rowNames.removeAt(i);
            rowTypes.removeAt(i);
            rowAutoIncrement.removeAt(i);
            i--;
            continue;
        }

        mainLayout->addWidget(new QLabel(rowNames[i]), i, 0);
        if (QRegExp("\\b(date)\\b").indexIn(rowTypes[i]) > -1)
        {
            MyDateEdit *dataField = new MyDateEdit();
            dataFields.push_back(dataField);
            mainLayout->addWidget(dataField, i, 1);
            dataList.append("2000-01-01");
            continue;

        } else {
            MyLineEdit *dataField = new MyLineEdit();
            dataFields.push_back(dataField);
            if(QRegExp("\\b(int)\\b").indexIn(rowTypes[i]) > -1){
                dataField->setValidator(new QIntValidator(INT_MIN, INT_MAX, this));
                dataList.append(QString::number(NULL));
            } else {
                dataList.append("");
            }
            mainLayout->addWidget(dataField, i, 1);
        }
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

    QString addQuery = "INSERT INTO " + currentTable + " (";
    for(auto n : rowNames){

        addQuery.append(n + ",");

    }

    addQuery.replace(addQuery.size()-1, 1, ")");
    addQuery.append(" VALUES " + data);

    emit writeData(addQuery);
    close();

}

void AddWindow::onUpdateData(QWidget* obj, QString data){

    dataList[(dataFields.indexOf(obj))] = data;

}

void AddWindow::onCancelBtnClicked(){

    close();

}
