#include "books_add.h"
#include "ui_books_add.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include "read_excel.h"
#include "book.h"
#include "filedb.h"
#include <iostream>
#include "user.h"
#include <sstream>
#include "isbn-book_id.h"
#include "tool.h"
#include <QTextCodec>
#include<QRegExpValidator>
#include "config.h"
#include <QTextCodec>
#include <QString>

Books_add::Books_add(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Books_add)
{
    ui->setupUi(this);
    fmain = new Book_addOnly;

    connect(fmain,SIGNAL(send_returnSignal()),this,SLOT(reshow()));

}

Books_add::~Books_add()
{
    delete ui;
}


void Books_add::on_Add_return_clicked()
{
    emit send_AddSignal();
    this->close();
}

void Books_add::reshow()
{
    this->show();
}

void Books_add::on_delete_book_clicked(char* isbn)
{
    Utils mutils2 = Utils();

    Book book = mutils2.GetBook(isbn);

    if(mutils2.DeleteBook(book)==1)
    {
        QMessageBox msgBox;
        msgBox.setText("删除成功");
        msgBox.exec();
    }
    else {
        QMessageBox msgBox;
        msgBox.setText("删除失败");
        msgBox.exec();
    }

}

void Books_add::on_AddMany_clicked()
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


            Utils mutils2 = Utils();
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
            book.setClassification(ba.data());


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

            mutils2.AddBook(book);


            Book new_book = mutils2.GetBook(isbn);

            QString cla_2=new_book.getClassifition();
            QStringList cla_tem = cla_2.split(" ");

            int c_flag=0;

            for(int i=0;i< cla_tem.size();i++)
            {
                int x_tem;
                //qDebug()<<cla_tem[i]<<endl;
                x_tem=mutils2.TransformClassification(cla_tem[i]);
                //classification_id.push_back(x_tem);

                BookClassification bc = BookClassification();
                bc.setIsbn(isbn);
                //cout<<x_tem<<endl;
                if(x_tem==-1)continue;
                bc.setClassification(x_tem);

                if(mutils2.CheckBookClassificationExist(bc)==0)
                    mutils2.InsertBookClassification(bc);
                else continue;
            }

            sumBooks++;
    }
    QString success = QString::number(sumBooks);
    QMessageBox::information(NULL, QString::fromLocal8Bit(""), success + "本图书导入成功", QMessageBox::Ok);
}

void Books_add::on_AddOnly_clicked()
{
    fmain->show();
    this->close();
}
