#include "add_book.h"
#include "ui_add_book.h"
#include "book.h"
#include "tool.h"
#include <QMessageBox>
#include <isbn-book_id.h>

Add_Book::Add_Book(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Add_Book)
{
    ui->setupUi(this);
}

Add_Book::~Add_Book()
{
    delete ui;
}

void Add_Book::on_pushButton_return_2_clicked()
{
    emit send_returnSiganl();
    this->close();
}

void Add_Book::setIsbn(char *ISBN)
{
    strcpy(id,ISBN);
}

void Add_Book::on_submit_2_clicked()
{
    cout<<"idddddddddddd"<<id<<endl;
    Utils mutils = Utils();

    Book book;
    book = mutils.GetBook(id);
    //cout<<book.getIsbn()<<endl;


    Book book_2 = mutils.GetBook(id);
    int old_left =book_2.getLeft();
    cout<<"old_lfete"<<book_2.getLeft()<<endl;
    int old_storage=book_2.getStorage();
    //cout<<old_storage<<endl;

    int flag = 0;
    QString str2 = ui->add_num->text();
    QByteArray ba2 = str2.toLocal8Bit();
    char *number = ba2.data();
    if(strlen(number) > 2){
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText("数据过大");
            msgBox.exec();
        }
    }
    for (int i = 0; i < strlen(number); i ++ ){
        if (number[i]<'0'||number[i]>'9')
        {
            if (number[i] == '-'){
                if (i != 0){
                    if(!flag){
                        flag = 1;
                        QMessageBox msgBox;
                        msgBox.setText("请检查负号");
                        msgBox.exec();
                        break;
                    }

                }
                else continue;
            }
            if (!flag){
                flag = 1;
                QMessageBox msgBox;
                msgBox.setText("只能输入0-9数字或者负号");
                msgBox.exec();
                break;
            }

        }
    }
    //const char* check_result1 = mutils.CheckBookIsbn(isbn);

    if(flag==1)return;
    int num=ui->add_num->text().toInt();
    //cout<<num<<endl;
    if(num+old_left<=0||num==0)
    {
        QMessageBox msgBox;
        msgBox.setText("输入错误");
        msgBox.exec();
    }
    else
    {
        if(num>0)
        {
            int id_total = book.getIdTotal();
            book_2.setLeft(old_left+num);
            cout<<"""asdadsdasdas"<<old_left+num<<endl;
            book_2.setStorage(old_storage+num);
            book_2.setIdTotal(id_total+num);

            for(int i=id_total+1;i<=id_total+num;i++)
            {
                IsbnBookId ib = IsbnBookId();
                cout<<i<<endl;
                ib.setIsbn(book.getIsbn());
                ib.setBookId(i);
                ib.setIsBorrowed(0);
                ib.setTimeBorrow(" ");
                ib.setBorrowAccount(" ");
                //ib.setIsBorrowed(0);

                mutils.InsertIsbnBookId(ib);
            }
            mutils.UpdateBook(book,book_2);

            QMessageBox msgBox;
            msgBox.setText("操作成功");
            msgBox.exec();
            on_pushButton_return_2_clicked();
        }
        else {
            int id_total = book.getIdTotal();
            book_2.setLeft(old_left+num);
            book_2.setStorage(old_storage+num);
            book_2.setIdTotal(id_total);



            int nowtotal=id_total+num;

            int cnt=0;

            int flag=0;

            for(int i=0;i<=id_total;i++)
            {
                IsbnBookId ib =IsbnBookId();

                ib.setIsbn(book.getIsbn());
                ib.setBookId(i);
                ib.setIsBorrowed(0);

                if(mutils.CheckIsbnBookIdExist(ib))
                {
                    if(!mutils.CheckIfBookIdBorrowed(book,i))
                    {
                        if(cnt>nowtotal)
                        {
                            mutils.DeleteIsbnBookId(ib);
                        }
                        cnt++;
                    }
                }
            }
            if(cnt+num<0)
            {
                QMessageBox msgBox;
                msgBox.setText("图书被借出，可删除数量不足");
                msgBox.exec();
            }
            else {
                mutils.UpdateBook(book,book_2);
                QMessageBox msgBox;
                msgBox.setText("操作成功");
                msgBox.exec();
                on_pushButton_return_2_clicked();
            }

        }

    }


}


