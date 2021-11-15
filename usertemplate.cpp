#include "usertemplate.h"
#include "ui_usertemplate.h"
#include"person.h"
#include "partition.h"
#include "book_ditails.h"
#include "loadpage.h"

usertemplate::usertemplate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usertemplate)
{
    ui->setupUi(this);

    fmain = new Person;

    connect(this,SIGNAL(sendsignal(char*)),fmain,SLOT(get_student_info(char*)));

    connect(fmain,SIGNAL(sendSignal()),this,SLOT(reshow()));

    book_rank = new Book_Rank;

    connect(this,SIGNAL(sendsignal(char*)),book_rank,SLOT(get_student_info(char*)));

    connect(book_rank,SIGNAL(sendSignal()),this,SLOT(reshow()));

    pt = new Partition;
    lp = new LoadPage;
    bookditail =new Book_Ditails;
    QObject::connect(lp,SIGNAL(Partitionpage()),pt,SLOT(Show_Partitionpage()));
    QObject::connect(pt,SIGNAL(listwidget_clicked(int, User)),lp,SLOT(Show_Loadpage(int, User)));
    QObject::connect(lp,SIGNAL(ISBN_to_main_SIGNAL(QString, User)),bookditail,SLOT(show_bookditals(QString, User)));

    connect(pt,SIGNAL(sendsignal()),this,SLOT(reshow()));

   /* connect(this,SIGNAL(sendsignal(char*)),partition,SLOT(get_student_info(char*)));

    connect(partition,SIGNAL(sendSignal()),this,SLOT(reshow()));*/

    manager_interface = new Manager_Interface;
//    manager_interface->get_student_info(this->getID());

    connect(this,SIGNAL(sendsignal(char*)),manager_interface,SLOT(get_student_info(char*)));

    connect(manager_interface,SIGNAL(sendSignal()),this,SLOT(reshow()));


}

usertemplate::~usertemplate()
{
    delete ui;
}

void usertemplate::on_pushButton_4_clicked()
{
    //跳转到个人
   // cout<<this->getID()<<endl;
    emit sendsignal(this->getID());
    fmain->show();
    this->close();
}

void usertemplate::reshow()
{
    this->show();
}

void usertemplate::get_student_info(char *id)
{
    this->setID(id);
    //cout<<"?"<<this->ID<<endl;
}

void usertemplate::on_pushButton_clicked()
{
    //跳转到榜单
    emit sendsignal(this->getID());
    book_rank->show();
    this->close();
}

void usertemplate::on_pushButton_3_clicked()
{
    //跳转到分区
    //emit sendsignal(this->getID());
    //cout<<"tiaozhuandaofenqu"<<endl;

    pt->get_info(this->getID());
    pt->show();

    //cout<<"showwanle"<<endl;
    this->hide();
}

void usertemplate::on_pushButton_2_clicked()
{
    //转到推荐搜索
    emit sendsignal(this->getID());
    manager_interface->show();
    this->close();
}

void usertemplate::on_pushButton_5_clicked()
{

    this->close();
}
