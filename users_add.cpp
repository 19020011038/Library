#include "users_add.h"
#include "ui_users_add.h"
#include "user_addonly.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include "read_excel.h"
#include "book.h"
#include "filedb.h"
#include <iostream>
#include "user.h"
#include <QTextCodec>
#include "tool.h"


users_add::users_add(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::users_add)
{
    ui->setupUi(this);

    Utils mutils = Utils();
    User user_tem = User();
    user_tem.setAccount("19090012028");

    User user_test=User();
    user_test=mutils.GetUser(user_tem.getAccount());


    QString str2= QString::fromLocal8Bit(user_test.getName());

     ui->test->setText(str2);
    fmain =new user_addonly;
    connect(fmain,SIGNAL(send_returnSignal()),this,SLOT(reshow()));
}

users_add::~users_add()
{
    delete ui;
}

void users_add::on_pushButton_return_clicked()
{
    emit send_return2Signal();
    this->close();
}

void users_add::reshow()
{
    this->show();
}


void users_add::on_AddMany_clicked()
{
    QMessageBox::information(NULL, QString::fromLocal8Bit(""), "请选择Excel文件,文件中列序按照学号、密码、用户名、性别、专业排好", QMessageBox::Ok);
    QString excelPath = QFileDialog::getOpenFileName(this, "选择Exccel", "", tr("Excel (*.xls *.xlsx)"));


    if (excelPath.isEmpty()) {
        return;
    }
    ReadExcel read;
    excelPath.replace(QString("/"), QString("\\"));
    read.openExcel(excelPath);


    int col, row;
    read.getInfo(row, col);
    User user;

    int sumUsers = 0;


    for (int i = 1; i <= row; i++) {


            QByteArray ba;
            ba = read.getCellData(i,1).toLocal8Bit();
            char *student_id = ba.data();
            //cout<<isbn<<endl<<name<<endl;
            if(ba.size() ==0 ||ba.length()>=ACCOUNT_SIZE)continue;
            user.setAccount(student_id);

            QByteArray ba2;
            ba2 = read.getCellData(i,3).toLocal8Bit();
            char *name = ba2.data();
            //cout<<isbn<<endl<<name<<endl;
            if(ba2.size() ==0 ||ba2.length()>=USER_NAME_SIZE)continue;
            user.setName(name);

            QByteArray ba3;
            ba3 = read.getCellData(i,2).toLocal8Bit();
            char *password = ba3.data();
            //cout<<isbn<<endl<<name<<endl;
            if(ba3.size() ==0 ||ba3.length()>=PASSWORD_SIZE)continue;
            user.setPassword(password);

           // string name = read.getCellData(i, 3).toStdString();
          //  string password = read.getCellData(i, 2).toStdString();


            QByteArray ba4;
            ba4 = read.getCellData(i,5).toLocal8Bit();
            char *major = ba4.data();
            //cout<<isbn<<endl<<name<<endl;
            if(ba4.size() ==0 ||ba4.length()>=MAJOR_SIZE)continue;
            user.setMajor(major);


            user.setflag(0);
            user.setIsAdmin(0);
            user.setNumBorrowed(0);
            user.setNumAppointed(0);

            string sex = read.getCellData(i, 4).toStdString();
            //if (!checkCount(nummm))continue;
            int numC = read.getCellData(i, 4).toInt();
            if(numC!=0&&numC!=1)continue;
            user.setSex(numC);

            Utils mutils = Utils();
            mutils.InsertUser(user);

            sumUsers++;
    }
    QString success = QString::number(sumUsers);
    QMessageBox::information(NULL, QString::fromLocal8Bit(""), success + "个用户导入成功", QMessageBox::Ok);

}

void users_add::on_AddOnly_clicked()
{
    fmain->show();
    this->close();
}
