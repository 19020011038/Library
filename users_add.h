#ifndef USERS_ADD_H
#define USERS_ADD_H

#include <QMainWindow>
#include "user_addonly.h"

namespace Ui {
class users_add;
}

class users_add : public QMainWindow
{
    Q_OBJECT

public:
    explicit users_add(QWidget *parent = 0);
    ~users_add();

private slots:
    void on_pushButton_return_clicked();
    void on_AddOnly_clicked();
    void on_AddMany_clicked();
    void reshow();

signals:
    void send_return2Signal();

private:
    Ui::users_add *ui;
    user_addonly *fmain;
};

#endif // USERS_ADD_H
