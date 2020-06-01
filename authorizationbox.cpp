#include "authorizationbox.h"
#include "ui_authorizationbox.h"

AuthorizationBox::AuthorizationBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AuthorizationBox)
{
    ui->setupUi(this);
}

AuthorizationBox::~AuthorizationBox()
{
    delete ui;
}


void AuthorizationBox::on_usrEdit_textChanged(const QString &arg1)
{
    username = arg1;
}

void AuthorizationBox::on_pwdEdit_textChanged(const QString &arg1)
{
    password = arg1;
}

void AuthorizationBox::on_dbEdit_textChanged(const QString &arg1)
{
    database = arg1;
}

void AuthorizationBox::on_cancelBtn_clicked()
{
    emit closeApp();
    close();
}

void AuthorizationBox::on_loginBtn_clicked()
{
    emit sendData(username, password, database);
}
