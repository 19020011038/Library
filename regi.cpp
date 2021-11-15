#include "regi.h"
#include "ui_regi.h"
#include<iostream>
#include<string>
#include"all_file_classes.h"
#include"tool.h"
#include<string>
#include<QMessageBox>

using namespace std;

int sex_male = -1;
int sex_female = -1;

regi::regi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regi)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
}

regi::~regi()
{
    delete ui;
}

void regi::on_pushButton_clicked()
{
    this->close();
}

void regi::on_pushButton_2_clicked()
{
    bool flag_regi = true;
    bool account_right = true;
    bool password_right = true;
    Utils mUtils = Utils();

    QString str = ui->lineEdit->text();
    QByteArray ba = str.toLocal8Bit();
    char *account = ba.data();

    QString str2 = ui->lineEdit_2->text();
    QByteArray ba2 = str2.toLocal8Bit();
    char *password = ba2.data();

    QString str3 = ui->lineEdit_3->text();
    QByteArray ba3 = str3.toLocal8Bit();
    char *repet_password = ba3.data();

    QString str4 = ui->lineEdit_4->text();
    QByteArray ba4 = str4.toLocal8Bit();
    char *name = ba4.data();

    QString str5 = ui->lineEdit_5->text();
    QByteArray ba5 = str5.toLocal8Bit();
    char *major = ba5.data();


    if (strlen(account) == 0){
        QMessageBox msgBox;
        msgBox.setText("请输入账户");
        msgBox.exec();
        flag_regi = false;
    }else if (strlen(account) != 11){
        QMessageBox msgBox;
        msgBox.setText("账户必须是11位");
        msgBox.exec();
        flag_regi = false;
    }else if (strlen(password) == 0){
        QMessageBox msgBox;
        msgBox.setText("请输入密码");
        msgBox.exec();
        flag_regi = false;
    }else if (strlen(password) > 16){
        QMessageBox msgBox;
        msgBox.setText("密码最多16位");
        msgBox.exec();
        flag_regi = false;
    }else if (strlen(password) < 8){
        QMessageBox msgBox;
        msgBox.setText("密码最少8位");
        msgBox.exec();
        flag_regi = false;
    }else if (!mUtils.compair_const(password, repet_password)){
        QMessageBox msgBox;
        msgBox.setText("两次输入密码不一致");
        msgBox.exec();
        flag_regi = false;
    }else if (strlen(name) == 0){
        QMessageBox msgBox;
        msgBox.setText("请输入姓名");
        msgBox.exec();
        flag_regi = false;
    }else if(strlen(name) > 15){
        QMessageBox msgBox;
        msgBox.setText("姓名不得长于15个字符");
        msgBox.exec();
        flag_regi = false;
    }
    else if (strlen(major) == 0){
        QMessageBox msgBox;
        msgBox.setText("请输入专业");
        msgBox.exec();
        flag_regi = false;
    }else if (strlen(major) > 30){
        QMessageBox msgBox;
        msgBox.setText("专业不得长于30个字符");
        msgBox.exec();
        flag_regi = false;
    }
    else {
        for (int i = 0; i < strlen(account); i ++ ){
            char c = account[i];
            if (!(c>='0'&&c<='9')){
                account_right = false;
                break;
            }
        }
        for (int i = 0; i < strlen(password); i ++ ){
            char c = password[i];
            if (!(c<='z'&&c>='a') && !(c<='Z'&&c>='A') && !(c>='0'&&c<='9')){
                password_right = false;
                break;
            }
        }
        if (!(account_right&&password_right))
            flag_regi = false;
        if (!account_right){
            QMessageBox msgBox;
            msgBox.setText("账户为0-9数字");
            msgBox.exec();
        }
        if (!password_right){
            QMessageBox msgBox;
            msgBox.setText("密码仅可包含大小写英文字母和0-9数字");
            msgBox.exec();
        }

    }
    if (flag_regi){
        User get_user = User();
        get_user.setAccount(account);
        if (!mUtils.CheckUserExist(get_user)){
            if(mUtils.compair_const(password, repet_password)){
                if (sex_male != sex_female && (sex_male != -1 || sex_female != -1)){
                    if (sex_male == 2){
                        get_user.setSex(1);
                    }else{
                        get_user.setSex(0);
                    }
                    get_user.setName(name);
                    get_user.setMajor(major);
                    get_user.setFrooze(0);
                    get_user.setIsAdmin(0);
                    get_user.setPassword(password);
                    get_user.setNumBorrowed(0);
                    get_user.setNumAppointed(0);
                    if (mUtils.InsertUser(get_user)){
                        //cout<<"major is   "<<major<<endl;
                        //cout<<strlen(name)<<" name size"<<endl;
                        //cout<<strlen(major)<<" major size"<<endl;
                        QMessageBox msgBox;
                        msgBox.setText("注册成功");
                        msgBox.exec();
                        this->close();
                    }else{
                        QMessageBox msgBox;
                        msgBox.setText("注册失败");
                        msgBox.exec();
                    }
                }else{
                    cout<<"now male"<<sex_male<<endl;
                    cout<<"now female"<<sex_female<<endl;
                    QMessageBox msgBox;
                    msgBox.setText("请选择正确的性别");
                    msgBox.exec();
                }
            }else{
                QMessageBox msgBox;
                msgBox.setText("两次输入密码不同");
                msgBox.exec();
            }
        }else{
            QMessageBox msgBox;
            msgBox.setText("该账户已存在");
            msgBox.exec();
        }
    }
}

void regi::on_checkBox_stateChanged(int arg1)
{
    sex_male = arg1;
   // cout<<"man change  "<<arg1<<endl;
//    ui->checkBox->setCheckState(Qt::Checked);
    ui->checkBox_2->setCheckState(Qt::Unchecked);
}

void regi::on_checkBox_2_stateChanged(int arg1)
{
    sex_female = arg1;
    //cout<<"woman change  "<<arg1<<endl;
    ui->checkBox->setCheckState(Qt::Unchecked);
//    ui->checkBox_2->setCheckState(Qt::Checked);
}
