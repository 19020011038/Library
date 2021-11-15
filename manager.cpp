#include "manager.h"
#include "ui_manager.h"
#include <QDebug>
#include <vector>
#include <book.h>
#include <algorithm>
#include "searchandselect.h"
#include "user.h"
#include "tool.h"
#include <QMessageBox>
#include <QFileDialog>
#include "read_excel.h"
#include <iostream>
#include <sstream>
#include "isbn-book_id.h"
#include <QTextCodec>
#include "config.h"
#include <QTextCodec>
#include <QString>

QList<QList<QString>> t2DataList3;//数据
int t2RowIndex3 = 0;
vector<Book> t2result_select;
vector<Book> t2search_temp;
QString t2search_text;

//User user_manager;

int t2page_num = 0;

manager::manager(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::manager)
{
    ui->setupUi(this);

    fmain = new Book_addOnly;

    connect(fmain,SIGNAL(send_returnSignal()),this,SLOT(reshow()));

    QStringList header;
    header<<"预览图"<<"书名"<<"作者"<<"出版社"<<"出版时间"<<"ISBN"<<"分区"<<"总收藏数"<<"删除图书"<<"修改图书"<<"增加数量";
    pageT = new PageT(header, 5);
    ui->testLayout->addLayout(pageT);

    connect(pageT->pageWidget, SIGNAL(currentPageChanged(int)), this, SLOT(PageChange(int)));


    //利用search_btn_clicked信号加载数据，
    connect(ui->search_widget,SIGNAL(search_btn_clicked(QString,int)),this,SLOT(BtnLoadDataClick(QString,int)));

    //qDebug() << "main: " << t2search_text;

    connect(pageT,SIGNAL(item_is_clicked(QString)),this,SLOT(items_clicked(QString)));
}




//void manager::text_from_interface(QString str)
//{
//    t2search_text = str;
//    qDebug() << "interface：" << t2search_text;
//}

void manager::LoadPage(int pageIndex){

    t2DataList3.clear();//先清空，只缓存一页。如果有100万条，缓存到List不合适
//    int sz = t2result_select.size();

    //qDebug() << t2page_num << "SSSS" << t2result_select.size();

    int bas = (pageIndex - 1) * 5;
    for(int i = bas;i < min((int)t2result_select.size(), bas + 5);i++){//10行
        Book bk = t2result_select[i];
        QList<QString> Row;
        t2RowIndex3 += 1;
        Row.append(QString::fromLocal8Bit(bk.getImage()));
        Row.append(QString::fromLocal8Bit(bk.getName()));
        Row.append(QString::fromLocal8Bit(bk.getAuthor()));
        Row.append(QString::fromLocal8Bit(bk.getPublisher()));
        Row.append(QString::fromLocal8Bit(bk.getPublishDate()));
        Row.append(QString::fromLocal8Bit(bk.getIsbn()));
        Row.append(QString::fromLocal8Bit(bk.getClassifition()));
        Row.append(QString::number(bk.getNumBorrow()));
        t2DataList3.append(Row);
    }
    pageT->SetData(t2DataList3);
}

void manager::BtnLoadDataClick(QString str,int search_kind){

    t2result_select.clear();
    t2search_text = str;

    Utils tmUtils2 = Utils();
    QByteArray ba=t2search_text.toLocal8Bit();
    char *c=ba.data();

    if(search_kind & 1)
    {
        t2search_temp.clear();
        if(tmUtils2.GetBooksByBookName(c,t2search_temp))
        {
            t2result_select = t2search_temp;
        }
        else
        {
            qDebug() << "false";
        }
    }
    if(search_kind >> 1 & 1)
    {
        t2search_temp.clear();
        if(tmUtils2.GetBooksByAuthor(c,t2search_temp))
        {
            int flag = 0;
            for(int i = 0; i < (int)t2search_temp.size(); i++)
            {
                flag = 0;
                for(int j = 0; j < (int)t2result_select.size(); j++)
                {
                    if(t2search_temp[i].getIsbn() == t2result_select[j].getIsbn())
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                {
                    t2result_select.push_back(t2search_temp[i]);
                }
            }
        }
        else
        {
            //qDebug() << "false";
        }
    }
    if(search_kind >> 2 & 1)
    {
        t2search_temp.clear();
        Book bk_test;
        bk_test.setIsbn(c);
        if(tmUtils2.CheckBookExist(bk_test))
        {
            //qDebug() << "qdebug";
            t2result_select = t2search_temp;

            bk_test = tmUtils2.GetBookByIsbn(c);

            int flag = 0;
            for(int i = 0; i < (int)t2result_select.size(); i++)
            {
                if(t2result_select[i].getIsbn() == bk_test.getIsbn())
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
            {
                t2result_select.push_back(bk_test);
            }
        }
        else
        {
            //qDebug() << "false";
        }
    }
    if(search_kind >> 3 & 1)
    {
        t2search_temp.clear();
        int id = t2search_text.toInt();
        if(tmUtils2.GetBooksByClassificationId(id,t2search_temp))
        {
            //qDebug() << "qdebug";
            int flag = 0;
            for(int i = 0; i < (int)t2search_temp.size(); i++)
            {
                flag = 0;
                for(int j = 0; j < (int)t2result_select.size(); j++)
                {
                    if(t2search_temp[i].getIsbn() == t2result_select[j].getIsbn())
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                {
                    t2result_select.push_back(t2search_temp[i]);
                }
            }
        }
        else
        {
            //qDebug() << "false";
        }
    }


    vector<Book> bk_list2;

    for(int i = 0; i < t2result_select.size(); i++)
    {
        int flag = 0;
        for(int j = 0; j < bk_list2.size(); j++)
        {
            if(!strcmp(bk_list2[j].getIsbn(),t2result_select[i].getIsbn()))
            {
                flag = 1;
            }
        }
        if(flag == 0)
        {
            bk_list2.push_back(t2result_select[i]);
        }
    }
    t2result_select.clear();
    for(int i=0;i<bk_list2.size();i++)
    {
        t2result_select.push_back(bk_list2[i]);
    }


    t2page_num = (bk_list2.size() + 4) / 5;


    //qDebug() << "click ...."<<t2RowIndex3;
    pageT->pageWidget->setMaxPage(t2page_num);//假如有10页数据
    pageT->pageWidget->setCurrentPage(1);

    t2RowIndex3 = 0;




    LoadPage(1);//加载第一页

}

void manager::PageChange(int currentPage){

    //qDebug()<<"pageChagne"<<currentPage;
    this->LoadPage(currentPage);
}


void manager::on_Add_return_clicked()
{
    emit send_AddSignal();
    this->close();
}

void manager::reshow()
{
    this->show();
}

void manager::on_AddOnly_clicked()
{
    fmain->show();
    this->close();
}



void manager::on_AddMany_clicked()
{
    QMessageBox::information(NULL, QString::fromLocal8Bit(""), "请选择Excel文件,文件中列序按照ISBN、书名、作者、封面路径、出版社、出版时间、单价、总量、简介、分类排好", QMessageBox::Ok);
    QString excelPath = QFileDialog::getOpenFileName(this, "选择Exccel", "", tr("Excel (*.xls *.xlsx)"));

    if (excelPath.isEmpty()) {
        return;
    }
    ReadExcel read;
    excelPath.replace(QString("/"), QString("\\"));
    read.openExcel(excelPath);

    int col, row;
    read.getInfo(row, col);
    Book book;

    int sumBooks = 0;


    for (int i = 1; i <= row; i++) {

            QString str;
            QByteArray ba2;
            //qDebug()<<read.getCellData(i,2)<<endl;

            //string ISBN = read.getCellData(i, 1).toStdString();
            ba2 = read.getCellData(i,1).toLocal8Bit();
            char *isbn = ba2.data();

            //if (!checkISBN(ISBN))continue;
            book.setIsbn(ba2.data());

            QByteArray ba;
            ba = read.getCellData(i,10).toLocal8Bit();
            char *cla = ba.data();
            //qDebug()<<"dasdsd"<<read.getCellData(i,10)<<endl;
            book.setClassification(ba.data());

            Utils mutils = Utils();


            QByteArray ba3;
            ba3 = read.getCellData(i,2).toLocal8Bit();
            char *name = ba3.data();
            //cout<<isbn<<endl<<name<<endl;
            if(ba3.size() ==0 ||ba3.length()>=BOOK_NAME_SIZE)continue;
            book.setName(name);

            QByteArray ba4;
            ba4 = read.getCellData(i,3).toLocal8Bit();
            char *author = ba4.data();
            if(ba4.size() ==0 ||ba4.length()>=AUTHOR_SIZE)continue;
            book.setAuthor(author);

            QByteArray ba5;
            ba5 = read.getCellData(i,4).toLocal8Bit();
            char *image = ba5.data();
            if(ba5.size() ==0 ||ba5.length()>=IMAGE_SIZE)continue;
            book.setImage(image);

            QByteArray ba6;
            ba6 = read.getCellData(i,5).toLocal8Bit();
            char *publish = ba6.data();
            if(ba6.size() ==0 ||ba6.length()>=PUBLISHER_SIZE)continue;
            book.setPublisher(publish);

            QByteArray ba7;
            ba7 = read.getCellData(i,6).toLocal8Bit();
            char *publish_time = ba7.data();
            if(ba7.size() ==0 ||ba7.length()>=PUBLISH_DATE_SIZE)continue;
            book.setPublishDate(publish_time);

            QByteArray ba8;
            ba8 = read.getCellData(i,9).toLocal8Bit();
            char *description = ba8.data();
            //cout<<description<<endl;
            if(ba8.size() ==0 ||ba8.length()>=DESCRIPTION_SIZE)continue;
            book.setDescription(description);


            string nummm = read.getCellData(i, 8).toStdString();
            //if (!checkCount(nummm))continue;
            int numC = read.getCellData(i, 8).toInt();
            if(numC<=0)continue;
            string scoreee = read.getCellData(i, 7).toStdString();
            //if (!checkScore(scoreee))continue;
            float score = read.getCellData(i, 7).toFloat();
            if(score<=0)continue;
            book.setPrice(score);
            book.setIdTotal(numC-1);
            book.setStorage(numC);
            book.setLeft(numC);
            book.setNumMark(0);
            book.setNumBorrow(0);

            mutils.AddBook(book);


            Book new_book = mutils.GetBook(isbn);


            QString cla_2=QString::fromLocal8Bit(new_book.getClassifition());
            qDebug()<<"saddsadsdaa"<<cla_2<<endl;
            QStringList cla_tem = cla_2.split(" ");

            int c_flag=0;

            for(int i=0;i< cla_tem.size();i++)
            {
                int x_tem;
                //qDebug()<<cla_tem[i]<<endl;
                x_tem=mutils.TransformClassification(cla_tem[i]);
                //classification_id.push_back(x_tem);

                BookClassification bc = BookClassification();
                bc.setIsbn(isbn);
                if(x_tem==-1)continue;
                bc.setClassification(x_tem);

                if(mutils.CheckBookClassificationExist(bc)==0)
                    mutils.InsertBookClassification(bc);
                else continue;
            }

            sumBooks++;
    }
    QString success = QString::number(sumBooks);
    QMessageBox::information(NULL, QString::fromLocal8Bit(""), success + "本图书导入成功", QMessageBox::Ok);
}


manager::~manager()
{
    delete ui;
}

