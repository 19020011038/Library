#include "search_book.h"
#include "ui_search_book.h"
#include <QLineEdit>
#include <QDebug>
#include <string>
#include <user.h>
#include "tool.h"

search_book::search_book(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::search_book)
{
    ui->setupUi(this);

    //勾选几个box，Debug中输出对应搜索的范围，并在点击搜索之后打印输入框的搜索内容
//    connect(ui->searchline, SIGNAL(textEdited(QString)),
//            this, SLOT(slot_textEdited(QString)));
//    connect(ui->searchbutton, SIGNAL(clicked()),
//            this, SLOT(slot_btn_clicked()));

    connect(ui->searchbutton, SIGNAL(clicked(bool)),
            this, SLOT(slot_search()));
//    connect(ui->checkbox_bookname, &QCheckBox::clicked,
//            this, SLOT(slot_select()));
}




void search_book::slot_search()
{

    int search_kind = 0;
    QString strText = ui->searchline->text();
    QString str;

    //查询复选框是否被选中
    if(ui->checkbox_id->isChecked())
    {
        search_kind += 1;

//        string temp_strText = strText.toStdString();
//        const char * c = temp_strText.c_str();



        //emit text_to_interface(strText);

//        printf("%s\n",c);

    }
    if(ui->checkBox_name->isChecked())
    {
        search_kind += 2;
        str += "姓名";
    }
    if(ui->checkBox_major->isChecked())
    {
        search_kind += 4;
        str += "专业";
    }

    /*

    if(str.isEmpty())
    {
        qDebug() << "无分区，错误";
    }
    else
    {
        qDebug() << str;
    }

    if(!strText.isEmpty())
    {
        qDebug() << strText;
    }
    else
    {
        qDebug() << "无内容";
    }*/

    emit search_btn_clicked(strText,search_kind);
}

//QString SearchAndSelect::slot_select()
//{
//   return ui->checkbox_bookname->isChecked();
//}


//void SearchAndSelect::slot_text_edited(QString str)
//{
//    int text_len = str.size();
//    //没有任何输入的情况
//    if(text_len == 0)
//    {
//        m_iCurBtnStatus = ESEARCH;
//    }
//    else
//    {
//        m_iCurBtnStatus = ECLOSE;
//    }
//}

//void SearchAndSelect::slot_btn_clicked()
//{
//    if(m_iCurBtnStatus == ESEARCH)
//    {
//        qDebug() << "无输出";
//    }
//    else
//    {
//        m_pLineEdit->clear();
//        m_pLineEdit->setFocus();
//        m_iCurBtnStatus = ESEARCH;


//        qDebug() << m_pLineEdit;
//    }
//}

search_book::~search_book()
{
    delete ui;
}
