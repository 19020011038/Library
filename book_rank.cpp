#include "book_rank.h"
#include "ui_book_rank.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QDebug>
#include <vector>
#include <iostream>
#include "book.h"
#include "user.h"
#include "PageTable.h"
#include "tool.h"

User user_book_rank;

Book_Rank::Book_Rank(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Book_Rank)
{
    ui->setupUi(this);

    qDebug() << "[Debug] MyObject::test ";

    //表格不是直接用UI写的，是new出来的。
    //文件结构上 PageWidget 是 在PageTable对象中的。
    QStringList header;
    header<<"预览图"<<"书名"<<"作者"<<"出版社"<<"出版时间"<<"ISBN"<<"总借阅数";
    pageTable = new PageTable(header, 5);
    ui->testLayout1->addLayout(pageTable);
    header.clear();
    header<<"预览图"<<"书名"<<"作者"<<"出版社"<<"出版时间"<<"ISBN"<<"总收藏数";
    pageTable2 = new PageTable(header, 5);
    ui->testLayout2->addLayout(pageTable2);

    connect(pageTable->pageWidget, SIGNAL(currentPageChanged(int)), this, SLOT(PageChange(int)));
    connect(pageTable2->pageWidget, SIGNAL(currentPageChanged(int)), this, SLOT(PageChange2(int)));
    //connect(ui->btnLoadData, &QPushButton::clicked, this, SLOT(BtnLoadDataClick()));
    connect(pageTable,SIGNAL(item_is_clicked(QString)),this,SLOT(items_clicked(QString)));
    connect(pageTable2,SIGNAL(item_is_clicked(QString)),this,SLOT(items_clicked(QString)));

    connect(ui->btnLoadData,&QPushButton::clicked,[=](){
            BtnLoadDataClick();
        });


}

void Book_Rank::on_pushButton_return_clicked()
{
    emit sendSignal();
    cout<<"?sdaddasdadaasdadasda";
    this->close();
}

void Book_Rank::items_clicked(QString isbn_clicked)
{
    emit item_clicked(isbn_clicked, user_book_rank);
}

Utils muti = Utils();
QList<QList<QString>> DataList1;//数据
QList<QList<QString>> DataList2;//数据
int RowIndex1 = 0;
int RowIndex2 = 0;

void Book_Rank::LoadPage(int pageIndex){

    DataList1.clear();//先清空，只缓存一页。如果有100万条，缓存到List不合适
    if(muti.UpdateBorrowRank())
    {

        int bas = pageIndex == 1 ? 0 : 5;

        vector<Book> rank;

        qDebug() << "bas:" << bas;

        if(muti.GetBorrowRank(rank))
        {
            //qDebug() << rank[0].getName();
            //cout<< rank[0].getName() << endl;

            qDebug() << "ranksize:"<<rank.size();

            if(bas < rank.size())
            for(int i = bas;i < rank.size();i++){//10行
                Book bk = rank[i];
                QList<QString> Row;
                RowIndex1 += 1;
                Row.append(QString::fromLocal8Bit(bk.getImage()));
                Row.append(QString::fromLocal8Bit(bk.getName()));
                Row.append(QString::fromLocal8Bit(bk.getAuthor()));
                Row.append(QString::fromLocal8Bit(bk.getPublisher()));
                Row.append(QString::fromLocal8Bit(bk.getPublishDate()));
                Row.append(QString::fromLocal8Bit(bk.getIsbn()));
                Row.append(QString::number(bk.getNumBorrow()));
                DataList1.append(Row);
                //qDebug() << bk.getName();
                //qDebug() << Row;
            }
            pageTable->SetData(DataList1);
        }
        else
        {
          qDebug() << "false123";
        }

    }
    else
    {
        qDebug() << "false456";
    }
}


void Book_Rank::LoadPage2(int pageIndex){

    DataList2.clear();//先清空，只缓存一页。如果有100万条，缓存到List不合适
    if(muti.UpdateMarkRank())
    {

        int bas = pageIndex == 1 ? 0 : 5;

        vector<Book> rank;

        qDebug() << "mark bas:" << bas;

        if(muti.GetMarkRank(rank))
        {
            //qDebug() << rank[0].getName();
            //cout<< rank[0].getName() << endl;

            qDebug() << "mark ranksize:"<<rank.size();

            if(bas < rank.size())
            for(int i = bas;i < rank.size();i++){//10行
                Book bk = rank[i];
                QList<QString> Row;
                RowIndex2 += 1;
                Row.append(QString::fromLocal8Bit(bk.getImage()));
                Row.append(QString::fromLocal8Bit(bk.getName()));
                Row.append(QString::fromLocal8Bit(bk.getAuthor()));
                Row.append(QString::fromLocal8Bit(bk.getPublisher()));
                Row.append(QString::fromLocal8Bit(bk.getPublishDate()));
                Row.append(QString::fromLocal8Bit(bk.getIsbn()));
                Row.append(QString::number(bk.getNumMark()));
                DataList2.append(Row);
                //qDebug() << bk.getName();
                //qDebug() << Row;
            }
            pageTable2->SetData(DataList2);
        }
        else
        {
          qDebug() << "false123";
        }

    }
    else
    {
        qDebug() << "false456";
    }
}


void Book_Rank::BtnLoadDataClick(){

    //qDebug() << "click ...."<<RowIndex;
    pageTable->pageWidget->setMaxPage(2);//假如有2页数据
    pageTable->pageWidget->setCurrentPage(1);

    pageTable2->pageWidget->setMaxPage(2);//假如有2页数据
    pageTable2->pageWidget->setCurrentPage(1);

    RowIndex1 = 0;
    RowIndex2 = 0;
    LoadPage(1);//加载第一页
    LoadPage2(1);

}


void Book_Rank::PageChange(int currentPage){

    qDebug()<<"pageChagne"<<currentPage;
    this->LoadPage(currentPage);
}

void Book_Rank::PageChange2(int currentPage){

    qDebug()<<"pageChagne"<<currentPage;
    this->LoadPage2(currentPage);
}


Book_Rank::~Book_Rank()
{
    delete ui;
}

