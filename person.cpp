#include "person.h"
#include "ui_person.h"
#include "user.h"
#include "filedb.h"
#include <iostream>
#include <QDebug>
#include "tool.h"

using namespace  std;

Person::Person(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);

    borrow=new borrowing;

    connect(this,SIGNAL(sendID(char*)),borrow,SLOT(get_borrowbook(char*)));
    connect(borrow,SIGNAL(sendreturnSignal()),this,SLOT(reshow()));

    collection=new Collection;
    connect(this,SIGNAL(sendID_2(char*)),collection,SLOT(get_collection_book(char*)));
    connect(collection,SIGNAL(send_collect_returnSignal()),this,SLOT(reshow()));


    preb=new preborrow;
    connect(this,SIGNAL(sendID_3(char*)),preb,SLOT(get_preborrow(char*)));
    connect(preb,SIGNAL(send_preborrow_return_signal()),this,SLOT(reshow()));

    set=new setting;
    connect(this,SIGNAL(sendID_4(char*)),set,SLOT(get_info(char*)));
    connect(set,SIGNAL(send_set_return_signal()),this,SLOT(reshow()));
}

Person::~Person()
{
    delete ui;
}

void Person::on_pushButton_close_clicked()
{
    emit sendSignal();
    this->close();
}

void Person::on_borrow_clicked()
{
    emit sendID(ID);
    borrow->show();
    this->hide();
}

void Person::on_have_clicked()
{
    emit sendID_2(ID);
    collection->show();
    this->hide();
}

void Person::on_preborrow_clicked()
{
    emit sendID_3(ID);
    preb->show();
    this->hide();
}

void Person::on_setting_clicked()
{
    emit sendID_4(ID);
    set->show();

    this->hide();
}

void Person::reshow()
{
    this->show();
}

void Person::get_student_info(char* student_id)
{
    this->setID(student_id);


    Utils mutils = Utils();

    User user = mutils.GetUser(ID);

    QString textstring = QString::fromLocal8Bit(user.getAccount());

    ui->account->setText(textstring);

    QString name = QString::fromLocal8Bit(user.getName());
    qDebug()<<name<<endl;
    ui->name->setText(name);



    bool sex = user.getSex();
    QString sexT;
    if(sex==1)sexT="男";
    else if(sex==0)sexT="女";
    ui->sex->setText(sexT);

    QString major = QString::fromLocal8Bit(user.getMajor());
    ui->major->setText(major);



    //通过当前学号得到学生的具体信息，并且反馈到前端上
}

