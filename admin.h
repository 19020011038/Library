#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <books_add.h>
#include <users_add.h>
#include <manager.h>
#include <user_main.h>

namespace Ui {
class Admin;
}

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = 0);
    ~Admin();




private slots:
    void on_pushButton_return_clicked();
    void get_info(char *id);
    void on_book_clicked();
    void on_user_clicked();
    void reshow();

signals:
    void sendSignal_Admin();

private:
    Ui::Admin *ui;
    //Books_add *addbook;
    //users_add *adduser;
    user_main *userm;
    manager * bookm;

};

#endif // ADMIN_H
