#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QLineEdit *parent = nullptr);
private slots:

    void onTextEdited(QString text);

signals:

    void dataChanged(QWidget* obj, QString text);
};

#endif // MYLINEEDIT_H
