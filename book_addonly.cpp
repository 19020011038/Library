#include "book_addonly.h"
#include "ui_book_addonly.h"
#include "book.h"
#include "tool.h"
#include <QTextCodec>
#include <config.h>
#include "book-classification.h"
#include <QMessageBox>
#include <iostream>
#include <map>
#include<exception>
#include <QDebug>
using namespace  std;

Book_addOnly::Book_addOnly(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Book_addOnly)
{
    ui->setupUi(this);
}

Book_addOnly::~Book_addOnly()
{
    delete ui;
}

void Book_addOnly::on_pushButton_return_clicked()
{
    emit send_returnSignal();
    this->close();
}

void Book_addOnly::on_submit_clicked()
{
    Utils mutils = Utils();

    Book book;

    /*
    QString  str;
    char*  ch;
    QByteArray ba = str.toLocal8Bit(); // must
    ch=ba.data();*/

    int flag=0;

    QString str = ui->ISBN->text();

    QByteArray ba = str.toLocal8Bit();

    QString str2 = ui->ISBN->text();
    QByteArray ba2 = str2.toLocal8Bit();
    char *isbn = ba2.data();
    const char* check_result1 = mutils.CheckBookIsbn(isbn);
    if (mutils.compair_const("OK", check_result1)){
        book.setIsbn(isbn);
    }else{
        if(!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result1);
            msgBox.exec();
        }
    }
//    if(str2.length()<=0||str2.length()>=ISBN_SIZE)flag=1;


    str = ui->name->text();
    ba = str.toLocal8Bit();
    char *name = ba.data();
    const char* check_result2 = mutils.CheckBookName(name);
    if (mutils.compair_const("OK", check_result2)){
        book.setName(name);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result2);
            msgBox.exec();
        }
    }
//    if(str.length()<=0||str.length()>=BOOK_NAME_SIZE)flag=1;

//    book.setName(name);

    str = ui->author->text();
    ba = str.toLocal8Bit();
    char *author = ba.data();
    const char* check_result3 = mutils.CheckBookAuthor(author);
    if (mutils.compair_const("OK", check_result3)){
        book.setAuthor(author);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result3);
            msgBox.exec();
        }
    }
//    if(str.length()<=0||str.length()>=AUTHOR_SIZE)flag=1;
//    book.setAuthor(author);

    str = ui->image->text();
    ba = str.toLocal8Bit();
    char *image = ba.data();
    const char* check_result4 = mutils.CheckBookImage(image);
    if (mutils.compair_const("OK", check_result4)){
        book.setImage(image);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result4);
            msgBox.exec();
        }

    }
//    if(str.length()<=0||str.length()>=IMAGE_SIZE)flag=1;
//    book.setImage(image);

    str = ui->publish->text();
    ba = str.toLocal8Bit();
    char *publish = ba.data();
    const char* check_result5 = mutils.CheckBookPublisher(publish);
    if (mutils.compair_const("OK", check_result5)){
        book.setPublisher(publish);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result5);
            msgBox.exec();
        }

    }
//    if(str.length()<=0||str.length()>=PUBLISHER_SIZE)flag=1;
//    book.setPublisher(publish);

    str = ui->publish_date->text();

    ba = str.toLocal8Bit();
    char *publish_date = ba.data();
    const char* check_result6 = mutils.CheckBookPublishDate(publish_date);
    if (mutils.compair_const("OK", check_result6)){
        book.setPublishDate(publish_date);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result6);
            msgBox.exec();
        }

    }
//    if(str.length()<=0||str.length()>=PUBLISH_DATE_SIZE)flag=1;
//    book.setPublishDate(publish_date);


    str = ui->price->text();
    ba = str.toLocal8Bit();
    char *price_str = ba.data();
    if (strlen(price_str) > 8){
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText("价格过大");
            msgBox.exec();
        }
    }
    int count_point = 0;
    for (int i = 0; i < strlen(price_str); i ++)
    {
        if(flag == 1) break;
        //先判合法字符
        if (!(price_str[i]>='0'&&price_str[i]<='9') && price_str[i] != '.')
        {

            flag = 1;
            QMessageBox msgBox;
            msgBox.setText("请输入正确的价格");
            msgBox.exec();
            break;

        }else{
            //全部为合法字符了


            if (price_str[i]=='.')
            {
                //小数点前必须有数字
                if(i == 0){
                    flag = 1;
                    QMessageBox msgBox;
                    msgBox.setText("请输入正确的价格");
                    msgBox.exec();
                    break;
                }

                //判断只能有一个小数点
                count_point ++;
                if (count_point == 2){
                    flag = 1;
                    QMessageBox msgBox;
                    msgBox.setText("请输入正确的价格");
                    msgBox.exec();
                    break;
                }

            }
        }
    }


    if (!flag){
        float price = str.toFloat();
        const char* check_result7 = mutils.CheckBookPrice(price);
        if (mutils.compair_const("OK", check_result7)){
            book.setPrice(price);
        }else{
            if(!flag){
                flag = 1;
                QMessageBox msgBox;
                msgBox.setText(check_result7);
                msgBox.exec();
            }

        }


        cout<<book.getPrice()<<"    price"<<endl;

    }



    str = ui->num->text();//仍有爆int可能
    ba = str.toLocal8Bit();
    char *num_str = ba.data();
    if (strlen(num_str) > 3){
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText("库存数量过大");
            msgBox.exec();
        }
    }

    for (int i = 0 ; i < strlen(num_str); i ++ )
    {
        if (num_str[i]<'0' || num_str[i]>'9'){
            if(!flag){
                flag = 1;
                QMessageBox msgBox;
                msgBox.setText("请输入正确的库存数");
                msgBox.exec();
                break;
            }
        }
    }
    if (!flag)
    {

        int num = str.toInt();
        cout<<num<<"    num"<<endl;
//        if(num<=0)flag=1;
        if (mutils.compair_const("OK", mutils.CheckBookNum(num))){
            book.setIdTotal(num-1);
            book.setLeft(num);
            book.setStorage(num);
            book.setNumBorrow(0);
            book.setNumMark(0);
        }else{
            if (!flag){
                flag = 1;
                QMessageBox msgBox;
                msgBox.setText(mutils.CheckBookNum(num));
                msgBox.exec();
            }
        }

    }



    int cla[30]={0};
    cla[0]=ui->cla_0->isChecked();
    cla[1]=ui->cla_1->isChecked();
    cla[2]=ui->cla_2->isChecked();
    cla[3]=ui->cla_3->isChecked();
    cla[4]=ui->cla_4->isChecked();
    cla[5]=ui->cla_5->isChecked();
    cla[6]=ui->cla_6->isChecked();
    cla[7]=ui->cla_7->isChecked();
    cla[8]=ui->cla_8->isChecked();
    cla[9]=ui->cla_9->isChecked();
    cla[10]=ui->cla_10->isChecked();
    cla[11]=ui->cla_11->isChecked();
    cla[12]=ui->cla_12->isChecked();
    cla[13]=ui->cla_13->isChecked();
    cla[14]=ui->cla_14->isChecked();
    //cla[15]=ui->cla_15->isChecked();
    cla[15]=ui->cla_16->isChecked();
    cla[16]=ui->cla_17->isChecked();
    cla[17]=ui->cla_18->isChecked();
    cla[18]=ui->cla_19->isChecked();
    cla[19]=ui->cla_20->isChecked();
    cla[20]=ui->cla_21->isChecked();
    cla[21]=ui->cla_22->isChecked();


    QString clas;


    map<int,QString>mp;
    mp.insert({0,"哲学"});
    mp.insert({1,"人文社科综合"});
    mp.insert({2,"管理学"});
    mp.insert({3,"政治"});
    mp.insert({4,"法律"});
    mp.insert({5,"经济"});
    mp.insert({6,"文化/教育"});
    mp.insert({7,"语言/文学"});
    mp.insert({8,"艺术"});
    mp.insert({9,"历史"});
    mp.insert({10,"数学"});
    mp.insert({11,"物理"});
    mp.insert({12,"化学/材料"});
    mp.insert({13,"理工综合"});
    mp.insert({14,"地球科学"});
    mp.insert({15,"生物"});
    mp.insert({16,"医学/药学"});
    mp.insert({17,"农业/水产",});
    mp.insert({18,"工业技术"});
    mp.insert({19,"计算机/网络"});
    mp.insert({20,"环境"});
    mp.insert({21,"其他"});

    int clas_num = 0;
    for(int i=0;i<=21;i++)
    {
        if(cla[i]==1)
        {
            clas_num ++;
            clas+=mp[i];
            clas+=" ";
            /*
            BookClassification bc = BookClassification();

            bc.setIsbn(isbn);
            bc.setClassification(i);

            if(mutils.CheckBookClassificationExist(bc)==0&&flag==0)
            {
                mutils.InsertBookClassification(bc);
            }*/
        }
    }
    if (clas_num == 0){
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText("请选择分区");
            msgBox.exec();
        }

    }

    if (clas_num > 3){
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText("至多选择三个分区");
            msgBox.exec();
        }

    }

    if (!flag){
        qDebug()<<clas<<endl;

        ba = clas.toLocal8Bit();
        char *Classification = ba.data();
        if(clas.length()<=0||clas.length()>=CLASSIFICATION_SIZE)flag=1;

        book.setClassification(Classification);
    }


    str = ui->description->toPlainText();
    ba = str.toLocal8Bit();
//    if(str.length()==0||str.length()>=DESCRIPTION_SIZE)flag=1;

    char *description =ba.data();
    const char* check_result8 = mutils.CheckBookDescription(description);
    if (mutils.compair_const("OK", check_result8)){
            book.setDescription(description);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result8);
            msgBox.exec();
        }

    }


    if(mutils.CheckBookExist(book)==0&&flag==0)
    {
        if(mutils.AddBook(book)==0)flag=1;
        else
        {
            for(int i=0;i<=21;i++)
            {
                if(cla[i]==1)
                {
                    BookClassification bc = BookClassification();

                    bc.setIsbn(isbn);
                    bc.setClassification(i);

                    if(mutils.CheckBookClassificationExist(bc)==0&&flag==0)
                    {
                        mutils.InsertBookClassification(bc);
                    }
                }
            }
        }
    }
    else flag=1;

    //Book checkBook = mutils.GetBook(book.getIsbn());

    /*cout<<checkBook.getName()<<endl;
    cout<<checkBook.getClassifition()<<endl;

    Book*/

    //ui->label->setText(qs);

    if(flag == 1)
    {
//        QMessageBox msgBox;
//        msgBox.setText("输入出现错误");
//        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("提交成功");
        msgBox.exec();
        on_pushButton_return_clicked();

    }

}
