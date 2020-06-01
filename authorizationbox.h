#ifndef AUTHORIZATIONBOX_H
#define AUTHORIZATIONBOX_H

#include <QWidget>
#include <QString>
#include <QStringList>

namespace Ui {
class AuthorizationBox;
}

class AuthorizationBox : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorizationBox(QWidget *parent = nullptr);
    ~AuthorizationBox();
    void uptadeDbList();

signals:

    void sendData(QString username, QString password, QString database);
    void closeApp();

private slots:
    void on_usrEdit_textChanged(const QString &arg1);

    void on_pwdEdit_textChanged(const QString &arg1);

    void on_dbEdit_textChanged(const QString &arg1);

    void on_cancelBtn_clicked();

    void on_loginBtn_clicked();

    void on_usrEdit_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::AuthorizationBox *ui;
    QString username;
    QString password;
    QString database;
};

#endif // AUTHORIZATIONBOX_H
