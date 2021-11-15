#include "preborrow.h"
#include "ui_preborrow.h"

#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QStringList>
#include <QString>
#include <QPushButton>
#include <QDebug>
#include <vector>
#include "tool.h"
#include "isbn-book_id.h"
#include <iostream>
#include <QMessageBox>


using namespace std;

preborrow::preborrow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::preborrow)
{
     ui->setupUi(this);
}

preborrow::~preborrow()
{
    delete ui;
}

void preborrow::setID(char *id)
{
    strcpy(ID,id);
}

void preborrow::get_preborrow(char* sutdent_id)
{
    strcpy(ID,sutdent_id);



    vector<Book> result;



    Utils mutils = Utils();

    User user = mutils.GetUser(ID);

    cout<<"user"<<user.getAccount()<<endl;

    //cout<<"bug"<<endl;
    ui->tableView->setMinimumSize(700, 500);
    ui->tableView->verticalHeader()->hide();

    QStandardItemModel *tableModel = new QStandardItemModel(this);
    ui->tableView->setModel(tableModel); // recommend to set model before detail settings

    // set columns
    QStringList columnTitles;
    columnTitles << "书名" << "作者" << "ISBN" << "出版社"<< "取消预约" ;
    tableModel->setHorizontalHeaderLabels(columnTitles);

    if(!mutils.GetAppointmentList(user, result))
    {
        QMessageBox msgBox;
        msgBox.setText("暂无预约");
        msgBox.exec();
    }


    for(int i=0;i<result.size();i++)
    {

        //Book tem=GetBook(result[i].getIsbn());
        tableModel->setItem(i, 0, new QStandardItem(QString::fromLocal8Bit(result[i].getName())));
        tableModel->setItem(i, 1, new QStandardItem(QString::fromLocal8Bit(result[i].getAuthor())));
        tableModel->setItem(i, 2, new QStandardItem(QString::fromLocal8Bit(result[i].getIsbn())));
        tableModel->setItem(i, 3, new QStandardItem(QString::fromLocal8Bit(result[i].getPublisher())));


       // QString isbn = QString(QLatin1String(tem.getIsbn()));

        //int id= result[i].getBookId(tem.getIsbn());

        char *isbn =result[i].getIsbn();

        QPushButton *preborrow_book_button=new QPushButton("取消预约");

        preborrow_book_button->setProperty("id", i); // set custom property
        preborrow_book_button->setProperty("isbn", QString(QLatin1String(isbn)));
        preborrow_book_button->setProperty("status", "normal");

        connect(preborrow_book_button,SIGNAL(clicked()),this,SLOT(delete_preborrow()));

        ui->tableView->setIndexWidget(tableModel->index(tableModel->rowCount() - 1, 4), preborrow_book_button);
    }

}


void preborrow::on_pushButton_return_clicked()
{
    emit send_preborrow_return_signal();
    this->close();
}

void preborrow::delete_preborrow()
{
    QPushButton *button=(QPushButton*)sender();
    Utils mutils = Utils();
    User user = mutils.GetUser(ID);
    QString str1 = button->property("isbn").toString();

    QByteArray ba = str1.toLatin1();
    char *c_str2 = ba.data();

    Book book = mutils.GetBook(c_str2);

    //Utils mutils = Utils();

    //User user = mutils.GetUser(student_id);

    //Book book = mutils.GetBook(ISBN);

    if(mutils.PreAppoint(user,book)==1)
    {
        QMessageBox msgBox;
        msgBox.setText("取消预约成功");
        msgBox.exec();
        emit send_preborrow_return_signal();
        this->close();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("取消预约失败");
        msgBox.exec();
        this->repaint();
    }
    /*
     * 修改用户信息，将该书的预约状态取消
     * 更改对应数据文件
     * 更改该窗口界面
     *
     */
}

void preborrow::get_bookdetail(char *ISBN){

}
