#include "user_addonly.h"
#include "ui_user_addonly.h"
#include "user.h"
#include "tool.h"
#include <QMessageBox>

user_addonly::user_addonly(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::user_addonly)
{
    ui->setupUi(this);
}

user_addonly::~user_addonly()
{
    delete ui;
}


void user_addonly::on_pushButton_return_clicked()
{
    emit send_returnSignal();
    this->close();
}

void user_addonly::on_submit_clicked()
{
    User user;

    Utils mutils = Utils();


    int flag=0;
    //cout<<"???";

    /*
    QString str = ui->ISBN->text();

    char isbn[ISBN_SIZE];
    QByteArray ba = str.toLocal8Bit();
    isbn = ba.data();
    if(str.length()<=0||str.length()>=ISBN_SIZE)flag=1;

    book.setIsbn(isbn);*/

    QString str = ui->account->text();
    QByteArray ba = str.toLocal8Bit();
    char *account = ba.data();
    const char* check_result1 = mutils.CheckUserAccount(account);
    if (mutils.compair_const("OK", check_result1)){
            user.setAccount(account);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result1);
            msgBox.exec();
        }

    }
//    if(str.length()<=0 || str.length()>=ACCOUNT_SIZE)flag=1;

//    user.setAccount(account);


    str = ui->password->text();
    ba = str.toLocal8Bit();
    char *password = ba.data();
    const char* check_result2 = mutils.CheckUserPassword(password);
    if (mutils.compair_const("OK", check_result2)){
            user.setPassword(password);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result2);
            msgBox.exec();
        }

    }
//    if(str.length()<=0 || str.length()>=PASSWORD_SIZE)flag=1;

//    user.setPassword(password);

    str = ui->name->text();
    ba = str.toLocal8Bit();
    char *name = ba.data();
    const char* check_result3 = mutils.CheckUserName(name);
    if (mutils.compair_const("OK", check_result3)){
            user.setName(name);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result3);
            msgBox.exec();
        }

    }
//    if(str.length()<=0 || str.length()>=USER_NAME_SIZE)flag=1;

//    user.setName(name);

    str = ui->major->text();
    ba=str.toLocal8Bit();
    char *major = ba.data();
    const char* check_result4 = mutils.CheckUserMajor(major);
    if (mutils.compair_const("OK", check_result4)){
            user.setMajor(major);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result4);
            msgBox.exec();
        }

    }
//    if(str.length()<=0||str.length()>=MAJOR_SIZE)flag=1;

//    user.setMajor(major);





    int sex;
    if(ui->sex_male->isChecked())sex=1;
    else if(ui->sex_female->isChecked())sex=0;
    else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText("请选择性别");
            msgBox.exec();
        }
    }
    if (!flag){
        user.setSex(sex);
    }


    if (!flag){
        user.setIsAdmin(0);
        user.setNumAppointed(0);
        user.setNumBorrowed(0);

        user.setFrooze(0);
    }


   // cout<<user.getAccount()<<endl;

    if(mutils.CheckUserExist(user)==0&&flag==0)
    {
        if(mutils.InsertUser(user)==1)
        {
            QMessageBox msgBox;
            msgBox.setText("操作成功");
            msgBox.exec();
        }
        else {
            QMessageBox msgBox;
            msgBox.setText("账户已存在");
            msgBox.exec();
        }

    }
    else
    {
//        QMessageBox msgBox;
//        msgBox.setText("输入出现错误");
//        msgBox.exec();
    }



}
