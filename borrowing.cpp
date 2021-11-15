#include "borrowing.h"
#include "ui_borrowing.h"
#include "tool.h"
#include "book.h"
#include "isbn-book_id.h"
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QStringList>
#include <QString>
#include <QPushButton>
#include <QDebug>
#include <vector>
#include <iostream>
#include <QMessageBox>
using namespace std;


borrowing::borrowing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::borrowing)
{
    ui->setupUi(this);
}

borrowing::~borrowing()
{
    delete ui;
}

void borrowing::set_ID(char *id)
{
    strcpy(ID,id);
}

void borrowing::get_borrowbook(char* student_id)//将该学生借阅的每一本书都添加到Qtable中
{
    strcpy(ID,student_id);

    // add contents
    Utils mutils = Utils();
    vector<IsbnBookId> result;



    User user = mutils.GetUser(ID);
    cout<<user.getAccount()<<endl;



    if(mutils.GetBorrowingList(user, result)==0)
    {
        QMessageBox msgBox;
        msgBox.setText("暂无借书");
        msgBox.exec();
    }

    for (int i = 0; i <result.size(); i ++){
        cout<< result.at(i).getIsBorrowed()<<"  hahah"<<endl;
    }

    ui->tableView->setMinimumSize(700, 500);
    ui->tableView->verticalHeader()->hide();

    QStandardItemModel *tableModel = new QStandardItemModel(this);
    ui->tableView->setModel(tableModel); // recommend to set model before detail settings


    // set columns
    QStringList columnTitles;
    columnTitles << "书名" << "作者" << "ISBN" << "出版社"<<"图书编号"<< "还书" ;
    tableModel->setHorizontalHeaderLabels(columnTitles);


    for(int i=0;i<result.size();i++)
    {

        Book tem=mutils.GetBook(result[i].getIsbn());

        tableModel->setItem(i, 0, new QStandardItem(QString::fromLocal8Bit(tem.getName())));
        tableModel->setItem(i, 1, new QStandardItem(QString::fromLocal8Bit(tem.getAuthor())));
        tableModel->setItem(i, 2, new QStandardItem(QString::fromLocal8Bit(tem.getIsbn())));
        tableModel->setItem(i, 3, new QStandardItem(QString::fromLocal8Bit(tem.getPublisher())));
        tableModel->setItem(i, 4, new QStandardItem(QString::number(result[i].getBookId())));


       // QString isbn = QString(QLatin1String(tem.getIsbn()));

        int id= result[i].getBookId();

        //cout<<"id"<<id<<endl;

        char *isbn =tem.getIsbn();

        QPushButton *return_book_button=new QPushButton("还书");

        return_book_button->setProperty("id", id); // set custom property
        return_book_button->setProperty("isbn", QString(QLatin1String(isbn)));
        return_book_button->setProperty("status", "normal");

        connect(return_book_button,SIGNAL(clicked()),this,SLOT(return_book()));

        ui->tableView->setIndexWidget(tableModel->index(tableModel->rowCount() - 1, 5), return_book_button);
        //将对应数据放到tableView中


      /*  QPushButton *book_button=new QPushButton("图书详情");

        book_button->setProperty("id", id); // set custom property
        book_button->setProperty("isbn", QString(QLatin1String(isbn)));
        book_button->setProperty("status", "normal");

        connect(book_button,SIGNAL(clicked()),this,SLOT(get_bookdetail(isbn)));

        ui->tableView->setIndexWidget(tableModel->index(tableModel->rowCount() - 1, 5), book_button);*/
        //将对应数据放到tableView中
    }
}

void borrowing::return_book()//根据书对应的ISBN和其对应的编号，进行还书
{
    cout<<"return"<<endl;
    QPushButton *button=(QPushButton*)sender();
    Utils mutils = Utils();
    User user = mutils.GetUser(ID);
    QString str1 = button->property("isbn").toString();

    QByteArray ba = str1.toLatin1();
    char *c_str2 = ba.data();

    Book book = mutils.GetBook(c_str2);

    //cout<<book.getIsbn()<<endl;

    int id = button->property("id").toInt();

    //cout<<id<<endl;

    if(mutils.Return(user,book,id)==1)
    {
        QMessageBox msgBox;
        msgBox.setText("还书成功");
        msgBox.exec();
        emit sendreturnSignal();
        this->close();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("还书失败");
        msgBox.exec();
        this->repaint();
    }
}

void borrowing::on_pushButton_return_clicked()
{
    emit sendreturnSignal();
    this->close();
}

void borrowing::get_bookdetail(char* ISBN)
{
    //通过该isbn，跳转到对应的图书详情页面，这个要和其他的做一个跳转
}
