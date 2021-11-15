#include "modify_student.h"
#include "ui_modify_student.h"
#include "user.h"
#include "tool.h"
#include <QMessageBox>

modify_student::modify_student(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modify_student)
{
    ui->setupUi(this);
}

modify_student::~modify_student()
{
    delete ui;
}


void modify_student::on_pushButton_return_clicked()
{
    emit send_returnSignal();
    this->close();
}

void modify_student::on_submit_clicked()
{
    User user;

    Utils mutils = Utils();


    int flag=0;

    QString str = ui->account->text();
    QByteArray ba = str.toLocal8Bit();
    char *account = ba.data();


    user.setAccount(account);



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


    User user_old = mutils.GetUser(student_id);
    cout<<"??";

    user.setIsAdmin(0);
    user.setNumAppointed(user_old.getNumAppointed());
    user.setNumBorrowed(user_old.getNumBorrowed());

    user.setFrooze(user_old.getFrooze());

    if(flag==0)
    {
        mutils.UpdateUser(user_old,user);
        QMessageBox msgBox;
        msgBox.setText("操作成功");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("输入出现错误");
        msgBox.exec();
    }
}

void modify_student::get_student_info(char *id)
{
    set_id(id);
    Utils mutils = Utils();
    User user = User();

    user = mutils.GetUser(student_id);

    char *ch;
    ch = user.getAccount();

    QString account = QString::fromLocal8Bit(ch);
    ui->account->setText(account);

    ch =user.getPassword();
    QString password = QString::fromLocal8Bit(ch);
    ui->password->setText(password);

    ch=user.getName();
    QString name = QString::fromLocal8Bit(ch);
    ui->name->setText(name);

    ch =user.getMajor();
    QString major =QString::fromLocal8Bit(ch);
    ui->major->setText(major);

    int sex=user.getSex();
    QString sex_t = QString("%1").arg(sex);

    if(sex==1)
    {
        ui->sex_male->setChecked(true);
    }
    else ui->sex_female->setChecked(true);

}

void modify_student::on_pushButton_1_clicked()
{
    const char* c ="19090012028";
    int len = strlen(c);
    char *b = new char[len];
    strcpy(b, c);

    Utils mutils = Utils();

    User user = User();
    user.setAccount(b);
    if(mutils.CheckUserExist(user))cout<<"find it"<<endl;

    this->get_student_info(b);
    //emit show_signal(b);
}
