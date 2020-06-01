#ifndef MYDATEEDIT_H
#define MYDATEEDIT_H

#include <QDateEdit>

class MyDateEdit : public QDateEdit
{
    Q_OBJECT
public:
    explicit MyDateEdit(QDateEdit *parent = nullptr);

private slots:

    void onDateChanged(QDate date);

signals:

    void dataChanged(QWidget* obj, QString text);

};

#endif // MYDATEEDIT_H
