#include "collection.h"
#include "ui_collection.h"
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QStringList>
#include <QString>
#include <QPushButton>
#include <QDebug>
#include <vector>
#include "tool.h"
#include "user.h"
#include <iostream>
#include <QMessageBox>

using namespace  std;


Collection::Collection(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Collection)
{
    ui->setupUi(this);
}

Collection::~Collection()
{
    delete ui;
}

void Collection::setID(char *id){
    strcpy(ID,id);
}

void Collection::on_pushButton_return_clicked()
{
    emit send_collect_returnSignal();
    this->close();
}

void Collection::delete_favour()
{
    QPushButton *button=(QPushButton*)sender();
    Utils mutils = Utils();
    User user = mutils.GetUser(ID);
    QString str1 = button->property("isbn").toString();

    QByteArray ba = str1.toLatin1();
    char *c_str2 = ba.data();

    Book book = mutils.GetBook(c_str2);

    if(mutils.SetMark(user,book,0)==1)
    {
        QMessageBox msgBox;
        msgBox.setText("取消收藏成功");
        msgBox.exec();
        emit send_collect_returnSignal();
        this->close();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("取消收藏失败");
        msgBox.exec();
        this->repaint();
    }

    /*
    this->get_collection_book(ID);*/


}

void Collection::get_collection_book(char* student_id)
{
    strcpy(ID,student_id);

    ui->tableView->setMinimumSize(700, 500);
    ui->tableView->verticalHeader()->hide();

    QStandardItemModel *tableModel = new QStandardItemModel(this);
    ui->tableView->setModel(tableModel); // recommend to set model before detail settings

    // set columns
    QStringList columnTitles;
    columnTitles << "书名" << "作者" << "ISBN" << "出版社"<< "收藏/取消收藏" ;
    tableModel->setHorizontalHeaderLabels(columnTitles);
    //tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents); // column fit the contents


    vector<Book> result;

    Utils mutils = Utils();

    User user = mutils.GetUser(ID);
    if(mutils.GetMarkList(user, result)==0)
    {
        QMessageBox msgBox;
        msgBox.setText("暂无收藏");
        msgBox.exec();
    }


    for(int i=0;i<result.size();i++)
    {
       // Book tem=mutils.GetBook(result[i].getIsbn());

        tableModel->setItem(i, 0, new QStandardItem(QString::fromLocal8Bit(result[i].getName())));
        tableModel->setItem(i, 1, new QStandardItem(QString::fromLocal8Bit(result[i].getAuthor())));
        tableModel->setItem(i, 2, new QStandardItem(QString::fromLocal8Bit(result[i].getIsbn())));
        tableModel->setItem(i, 3, new QStandardItem(QString::fromLocal8Bit(result[i].getPublisher())));

       // QString isbn = QString(QLatin1String(tem.getIsbn()));


        char *isbn =result[i].getIsbn();

        QPushButton *favour_book_button=new QPushButton("取消收藏");

        favour_book_button->setProperty("id", i); // set custom property
        favour_book_button->setProperty("isbn", QString(QLatin1String(isbn)));
        favour_book_button->setProperty("status", "normal");

        connect(favour_book_button,SIGNAL(clicked()),this,SLOT(delete_favour()));

        ui->tableView->setIndexWidget(tableModel->index(tableModel->rowCount() - 1, 4), favour_book_button);
        //将对应数据放到tableView中


        /*QPushButton *book_button=new QPushButton("图书详情");

        book_button->setProperty("id", i+result.size()); // set custom property
        book_button->setProperty("isbn", QString(QLatin1String(isbn)));
        book_button->setProperty("status", "normal");

        connect(book_button,SIGNAL(clicked()),this,SLOT(get_bookdetail(isbn)));

        ui->tableView->setIndexWidget(tableModel->index(tableModel->rowCount() - 1, 5), book_button);*/
        //将对应数据放到tableView中
    }

}

void Collection::get_bookdetail(char *ISBN)
{
    //
}
