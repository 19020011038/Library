#include "change_information.h"
#include "ui_change_information.h"
#include "tool.h"
#include "user.h"
#include <QByteArray>
#include <QMessageBox>

change_information::change_information(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::change_information)
{
    ui->setupUi(this);
    ui->new_password->setEchoMode(QLineEdit::Password); 
    ui->confirm_password->setEchoMode(QLineEdit::Password);
    
    ui->old_password->setEchoMode(QLineEdit::Normal);
}

change_information::~change_information()
{
    delete ui;
}

void change_information::setID(char *id)
{
    strcpy(ID,id);
}

void change_information::on_pushButton_change_password_clicked()
{
    int flag;
    QString real_password;
    
    Utils mutils = Utils();
    User user=mutils.GetUser(ID);
    User old_user = mutils.GetUser(ID);

    real_password=QString(QLatin1String(user.getPassword()));
    
    QString oldpassword;
    oldpassword=ui->old_password->text();

    QString newpassword;
    newpassword=ui->new_password->text();

    QByteArray ba = newpassword.toLocal8Bit();
    char *new_pass = ba.data();
    const char* check_result1 = mutils.CheckUserPassword(new_pass);
    if (mutils.compair_const("OK", check_result1)){
        flag = 0;
    }else{
        flag = 1;
    }


    QString confirmpassword;
    confirmpassword=ui->confirm_password->text();

    if(real_password!=oldpassword)
    {
        QMessageBox msgBox;
        msgBox.setText("旧的密码输入错误");
        msgBox.exec();
    }else if (flag){
        QMessageBox msgBox;
        msgBox.setText(check_result1);
        msgBox.exec();
    }
    else if(newpassword!=confirmpassword){
        QMessageBox msgBox;
        msgBox.setText("两次输入新密码不一致");
        msgBox.exec();
    }
    else
    {
        char*  ch;
        QByteArray ba = newpassword.toLatin1(); // must
        ch=ba.data();
        user.setPassword(ch);

        mutils.UpdateUser(old_user,user);

        QMessageBox msgBox;
        msgBox.setText("修改密码成功");
        msgBox.exec();

        on_pushButton_return_clicked();
        //实现修改密码的功能
    }
}

void change_information::on_pushButton_return_clicked()
{
    emit return_setting();
    this->close();
}
