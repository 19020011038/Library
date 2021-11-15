#include "setting.h"
#include "ui_setting.h"
#include "user.h"
#include "tool.h"
#include <iostream>

using namespace  std;

setting::setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    change_UI=new change_information;
    connect(this,SIGNAL(send_ID(char*)),change_UI,SLOT(setID(char*)));
    connect(change_UI,SIGNAL(return_setting()),this,SLOT(reshow()));
}

setting::~setting()
{
    delete ui;
}

void setting::get_info(char *id)
{
    strcpy(ID,id);

    Utils mutils = Utils();

    User student=mutils.GetUser(ID);

    QString textstring = QString::fromLocal8Bit(student.getAccount());

    ui->account->setText(textstring);

    QString name = QString::fromLocal8Bit(student.getName());
    ui->name_->setText(name);

    bool sex = student.getSex();
    QString sexT;
    if(sex==1)sexT="男";
    else sexT="女";
    ui->sex->setText(sexT);

    QString major = QString::fromLocal8Bit(student.getMajor());
    ui->major->setText(major);
}

void setting::setID(char *id)
{
    strcpy(ID,id);
}

void setting::on_exit_clicked(char* student_id)
{
    this->close();
}

void setting::on_pushButton_return_clicked()
{
    emit send_set_return_signal();
    this->close();
}

void setting::on_change_information_clicked()
{
    emit send_ID(ID);
    change_UI->show();
    this->hide();
}

void setting::reshow()
{
    this->show();
}

void setting::on_exit_clicked()
{
    this->close();
}
