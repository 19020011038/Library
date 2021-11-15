#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <iostream>
#include <QByteArray>
#include"all_file_classes.h"
#include"config.h"
#include"tool.h"
#include <iostream>
#include"formuser.h"
#include<string>
#include<QMessageBox>
#include<QLineEdit>
#include <QByteArray>
#include <QMessageBox>

using namespace std;

Utils mUtils = Utils();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    fmain=new usertemplate;

    connect(this,SIGNAL(sendsignal(char*)),fmain,SLOT(get_student_info(char*)));

    admin = new Admin;

    //connect(this,SIGNAL(sendAdmin(char*)),admin,SLOT())

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()
{

//    User user1 = User();
//    user1.setIsAdmin(1);
//    user1.setAccount("12345");
//    user1.setPassword("12345");
//    user1.setName("123451234512345");
//    user1.setSex(1);
//    user1.setMajor("computer science");
//    user1.setNumBorrowed(0);
//    user1.setNumAppointed(0);
//    user1.setFrooze(0);
//    mUtils.InsertUser(user1);
//    User user2 = mUtils.GetUser(user1.getAccount());
//    cout<<user2.getAccount()<<"  succc"<<endl;




//    User a = User();
//    const char* ac = "19020011034";
//    a = mUtils.GetUser(mUtils.const_to_char(ac));
//    ui->label_3->setNum(a.getSex());

//    const char* a = "12333";
//    char* ac = mUtils.const_to_char(a);
//    Book book = mUtils.GetBook(ac);
//    QString st = QString::fromLocal8Bit(book.getName());
//    ui->label_3->setText(st);


    bool flag = true;
    string get_account = ui->lineEdit->text().toStdString();
    string get_password = ui->lineEdit_2->text().toStdString();
    if (strlen(get_account.c_str()) == 0){
        flag = false;
        QMessageBox msgBox;
        msgBox.setText("请输入账户");
        msgBox.exec();
    }else{
        if (strlen(get_password.c_str()) == 0){
            flag = false;
            QMessageBox msgBox;
            msgBox.setText("请输入密码");
            msgBox.exec();
        }
    }
    if (flag){
        User get_user = User();
        get_user.setAccount(get_account.c_str());
        if (mUtils.CheckUserExist(get_user))
        {
            char char_account[ACCOUNT_SIZE];
            strcpy_s(char_account, get_account.c_str());
            const char* const_password = mUtils.GetUser(char_account).getPassword();
            bool flag = true;
            for (int i = 0 ; i < get_password.length(); i ++){
                if(const_password[i] != get_password.c_str()[i])
                    flag = false;
            }
            if (flag){
                if (mUtils.GetUser(char_account).getIsAdmin()){
                    this->close();
                    admin->show();
                }else{
                    // cout<<"ch"<<char_account<<endl;
                     strcpy(student_id,char_account);
                     emit sendsignal(student_id);
                     this->close();
                     fmain->exec();
                     /*usertemplate tem;
                     tem.exec();*/
                }

            }else{
                QMessageBox msgBox;
                msgBox.setText("密码错误");
                msgBox.exec();
            }
        }else{
            QMessageBox msgBox;
            msgBox.setText("用户不存在");
            msgBox.exec();
        }
    }

/*
        Book book = Book();
        book.setIsbn("2525");
        book.setLeft(10);
        book.setName("123");
        book.setImage("123");
        book.setPrice(1.1);
        book.setAuthor("我 ");
        book.setIdTotal(10);
        book.setNumMark(0);
        book.setStorage(10);
        book.setNumBorrow(77);
        book.setPublisher("123");
        book.setDescription("123");
        book.setPublishDate("2021-10-21");
        book.setClassification("123");
        book.setAvailableAppointmentTime("2021-10-21");
        if(mUtils.InsertBook(book))cout<<"insert success"<<endl;*/




//        for (int i = 0; i < book.getIdTotal(); i ++ ){
//            IsbnBookId ibi = IsbnBookId();
//            ibi.setIsbn(book.getIsbn());
//            ibi.setBookId(i);
//            ibi.setIsBorrowed(1);
//            ibi.setTimeBorrow("2021-10-21");
//            ibi.setBorrowAccount("123456");
//            mUtils.InsertIsbnBookId(ibi);
//        }


//        BookClassification bc = BookClassification();
//        bc.setIsbn(book.getIsbn());
//        bc.setClassification(1);
//        if(mUtils.InsertBookClassification(bc))cout<<"insert bc success"<<endl;

//        vector<Book> result;
//        mUtils.GetBooksOfClassification(1, result);
//        QString qstr = QString::fromStdString(result.at(0).getName());
//        ui->label_3->setText(qstr);
//        cout<<result.at(0).getName()<<endl;
//        cout<<"wocaonima"<<endl;
//        cout<<result.size()<<"   size"<<endl;
//        for (int i = 0 ; i < result.size(); i ++ )
//            cout<<result.at(i).getPrice()<<endl;




//    if (mUtils.UpdateMarkRank()){
//        cout<<"mark update success"<<endl;
//    }

//    if (mUtils.UpdateBorrowRank()){
//        cout<<"borrow update success"<<endl;
//    }
//    StudentBook sb = StudentBook();
//    sb.setIsbn("123");
//    sb.setMark(1);
//    sb.setAccount("123456");
//    sb.setRecommend(1);
//    sb.setIsAppointed(1);
//    sb.setIsInBorrowedHistory(1);
//    mUtils.InsertStudentBook(sb);


//    User user = User();
//    user.setAccount("19020011038");
//    User usera= mUtils.GetUser(user.getAccount());
//    vector<Book>result;

//    mUtils.GetAppointmentList(usera,result);

//    cout<<result.size()<<endl;
//    vector<Book> list;
//    if(mUtils.GetMarkRank(list)){
//        for (int i = 0 ; i < (int)list.size(); i ++ ){
//            cout << list.at(i).getIsbn()<<endl;
//        }
//        cout << list.size()<<endl;
//        cout<<"run";
//    }else{
//        cout<<"wrong";
//    }



//    User user = User();
//    user.setAccount("19020011038");
//    vector<IsbnBookId> list;
//    if (mUtils.GetBorrowingList(user, list)){
//        for (int i = 0; i < (int)list.size(); i ++ ){
//            cout << list.at(i).getBookId()<<endl;
//            cout << list.at(i).getIsbn()<<endl;
//        }
//    }


//    const char* a = "222\0";
//    char b[CLASSIFICATION_SIZE];
//    strcpy_s(b,a);
//    cout<<mUtils.TransformClassification(book.getClassifition());



//    if (mUtils.CheckBookExist(book)){
//        cout<<"1wdsf";
//    }else{
//        cout<<"0fdsfds";
//    }

//    IsbnBookId ibi = IsbnBookId();
//    ibi.setIsbn("123\0");
//    ibi.setBookId(0);
//    cout << mUtils.GetIsbnBookId(ibi.getIsbn(), ibi.getBookId()).getBookId();
















//    file.open(QIODevice::ReadOnly);
//    User user2 = User();
//    file.read((char*)&user2, sizeof(user));
//    cout << user2.getPassword();
//    QString aa = QString::fromStdString(book.getPublisher());
//    cout << book.getPublisher();
//    qint32 bb = strlen(mUtils.char_to_const(book.getPublisher()));
//    ui->label_3->setText(aa);
//    list.push_back(book);

//    test t;
//    t.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    regi r;
    r.exec();
}
