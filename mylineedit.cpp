#include "mylineedit.h"

MyLineEdit::MyLineEdit(QLineEdit *parent) : QLineEdit(parent)
{
    connect(this, SIGNAL(textEdited(const QString&)), this, SLOT(onTextEdited(QString)));
}

void MyLineEdit::onTextEdited(QString text){

    emit dataChanged(this, text);

}
