#include "mydateedit.h"

MyDateEdit::MyDateEdit(QDateEdit *parent) : QDateEdit(parent)
{
    connect(this, SIGNAL(dateChanged(const QDate&)), this, SLOT(onDateChanged(QDate)));
}

void MyDateEdit::onDateChanged(QDate date){

    emit dataChanged(this, date.toString(Qt::DateFormat::ISODate));

}
