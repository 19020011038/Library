#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);

    /*addbook = new Books_add;

    connect(addbook,SIGNAL(send_AddSignal()),this,SLOT(reshow()));

    adduser = new users_add;
    connect(adduser,SIGNAL(send_return2Signal()),this,SLOT(reshow()));*/

    userm = new user_main;
    connect(userm,SIGNAL(send_return2Signal()),this,SLOT(reshow()));

    bookm = new manager;
    connect(bookm,SIGNAL(send_AddSignal()),this,SLOT(reshow()));

}

Admin::~Admin()
{
    delete ui;
}


void Admin::on_pushButton_return_clicked()
{
    emit sendSignal_Admin();
    this->close();
}

void Admin::on_user_clicked()
{
    userm->show();
    this->close();
}

void Admin::on_book_clicked()
{
    bookm->show();
    this->close();
}

void Admin::get_info(char *id)
{

}

void Admin::reshow()
{
    this->show();
}
