#include "user_main.h"
#include "ui_user_main.h"
#include <QDebug>
#include <vector>
#include <algorithm>
#include "user.h"
#include "tool.h"
#include "read_excel.h"
#include <QMessageBox>
#include <QFileDialog>


QList<QList<QString>> tDataList3;//数据
int tRowIndex3 = 0;
vector<User> tresult_select;
vector<User> tsearch_temp;
QString tsearch_text;

//User user_manager_interface;

int tpage_num = 0;

user_main::user_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::user_main)
{
    ui->setupUi(this);

    fmain =new user_addonly;
    connect(fmain,SIGNAL(send_returnSignal()),this,SLOT(reshow()));
    QStringList header;
    header<<"学号"<<"姓名"<<"专业"<<"性别"<<"密码"<<"删除用户"<<"修改图书";
    userp = new user_page(header, 5);
    ui->testLayout->addLayout(userp);

    connect(userp->pageWidget, SIGNAL(currentPageChanged(int)), this, SLOT(PageChange(int)));

    //connect(ui->search_widget,SIGNAL(text_to_interface(QString)), this, SLOT(text_from_interface(QString)));

    //利用search_btn_clicked信号加载数据，
    connect(ui->search_widget_2,SIGNAL(search_btn_clicked(QString,int)),this,SLOT(BtnLoadDataClick(QString,int)));

    //qDebug() << "main: " << tsearch_text;

    connect(userp,SIGNAL(item_is_clicked(QString)),this,SLOT(items_clicked(QString)));
}

/*
void user_main::items_clicked(QString isbn_clicked)
{
    user_manager_interface.setName("Ge_Zuao");
    emit item_clicked(isbn_clicked, user_manager_interface);
}*/




void user_main::LoadPage(int pageIndex){

    tDataList3.clear();//先清空，只缓存一页。如果有100万条，缓存到List不合适
//    int sz = tresult_select.size();

    //qDebug() << tpage_num << "SSSS" << tresult_select.size();

    int bas = (pageIndex - 1) * 5;
    for(int i = bas;i < min((int)tresult_select.size(), bas + 5);i++){//10行
        User bk = tresult_select[i];
        if(bk.getIsAdmin()==1)
        {
            continue;
        }
        QList<QString> Row;
        tRowIndex3 += 1;
        Row.append(QString::fromLocal8Bit(bk.getAccount()));
        Row.append(QString::fromLocal8Bit(bk.getName()));
        Row.append(QString::fromLocal8Bit(bk.getMajor()));
        int sex=bk.getSex();
        QString sext;
        if(sex==1)
        {
            sext="男";
        }
        else sext="女";
        Row.append(sext);
        Row.append(QString::fromLocal8Bit(bk.getPassword()));
        tDataList3.append(Row);
    }
    userp->SetData(tDataList3);
}

void user_main::BtnLoadDataClick(QString str,int search_kind){

    tresult_select.clear();
    tsearch_text = str;

    QByteArray ba=tsearch_text.toLocal8Bit();
    char *c=ba.data();

    Utils mUtils2 = Utils();
    if(search_kind & 1)
    {
        tsearch_temp.clear();
        User user ;
        user.setAccount(c);
        if(mUtils2.CheckUserExist(user)==1)
        {
            user = mUtils2.GetUser(c);
            tsearch_temp.push_back(user);
            //qDebug() << "qdebug";
            tresult_select = tsearch_temp;
        }
        else
        {
            qDebug() << "false";
        }
    }
    if(search_kind >> 1 & 1)
    {
        tsearch_temp.clear();
        if(mUtils2.GetUserByName(c,tsearch_temp))
        {
            //qDebug() << "qdebug";
            int flag = 0;
            for(int i = 0; i < (int)tsearch_temp.size(); i++)
            {
                flag = 0;
                for(int j = 0; j < (int)tresult_select.size(); j++)
                {
                    if(tsearch_temp[i].getAccount() == tresult_select[j].getAccount())
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                {
                    tresult_select.push_back(tsearch_temp[i]);
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
        tsearch_temp.clear();
        //int id = tsearch_text.toInt();
        if(mUtils2.GetUserByMajor(c,tsearch_temp))
        {
            //qDebug() << "qdebug";
            int flag = 0;
            for(int i = 0; i < (int)tsearch_temp.size(); i++)
            {
                flag = 0;
                for(int j = 0; j < (int)tresult_select.size(); j++)
                {
                    if(tsearch_temp[i].getAccount() == tresult_select[j].getAccount())
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                {
                    tresult_select.push_back(tsearch_temp[i]);
                }
            }
        }
        else
        {
            //qDebug() << "false";
        }
    }

    vector<User> bk_list2;

    for(int i = 0; i < tresult_select.size(); i++)
    {
        int flag = 0;
        for(int j = 0; j < bk_list2.size(); j++)
        {
            if(!strcmp(bk_list2[j].getAccount(),tresult_select[i].getAccount()))
            {
                flag = 1;
            }
        }
        if(flag == 0)
        {
            bk_list2.push_back(tresult_select[i]);
        }
    }
    tresult_select.clear();
    for(int i=0;i<bk_list2.size();i++)
    {
        tresult_select.push_back(bk_list2[i]);
    }

    tpage_num = (tresult_select.size() + 4) / 5;


    //qDebug() << "click ...."<<tRowIndex3;
    userp->pageWidget->setMaxPage(tpage_num);//假如有10页数据
    userp->pageWidget->setCurrentPage(1);

    tRowIndex3 = 0;
    LoadPage(1);//加载第一页

}

void user_main::PageChange(int currentPage){

    //qDebug()<<"pageChagne"<<currentPage;
    this->LoadPage(currentPage);
}


void user_main::on_pushButton_return_clicked()
{
    emit send_return2Signal();
    //cout<<"eaijodsjxjdaiisjao "<<endl;
    this->close();
}

void user_main::reshow()
{
    this->show();
}


void user_main::on_AddMany_clicked()
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

            //User user_test=mutils.GetUser(student_id);

            //QString str2= QString::fromLocal8Bit(user_test.getName());

           // ui->test->setText(str2);

            /*vector<User>resUserr;
            resUserr.push_back(user);
            FileDB file("C:\\Users\\Lenovo\\Desktop\\temp\\");
            file.insert("user", resUserr);*/

            sumUsers++;
    }
    QString success = QString::number(sumUsers);
    QMessageBox::information(NULL, QString::fromLocal8Bit(""), success + "个用户导入成功", QMessageBox::Ok);

}

void user_main::on_AddOnly_clicked()
{
    fmain->show();
    this->close();
}


user_main::~user_main()
{
    delete ui;
}
