#include "manager_interface.h"
#include "ui_manager_interface.h"
#include <QDebug>
#include <vector>
#include <book.h>
#include <algorithm>
#include "searchandselect.h"
#include "user.h"
#include "unordered_map"
#include "tool.h"

QList<QList<QString>> DataList3;//数据
int RowIndex3 = 0;
vector<Book> result_select;
vector<Book> search_temp;
QString search_text;
Utils mUtils2 = Utils();
User user_manager_interface;
vector<Book> recommod_list;
int has_selected = 0;
unordered_map<int,string> mp;

int page_num = 0;

Manager_Interface::Manager_Interface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Manager_Interface)
{
    ui->setupUi(this);

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
    mp.insert({17,"农业/水产"});
    mp.insert({18,"工业技术"});
    mp.insert({19,"计算机/网络"});
    mp.insert({20,"环境"});
    mp.insert({21,"其它"});
}

void Manager_Interface::on_pushButton_return_clicked()
{
    emit sendSignal();
    this->close();
}

void Manager_Interface::get_student_info(char *id)
{
    this->setID(id);
    DataList3.clear();
    cout<<"in get stu info"<<id<<endl;
    cout<<"ID shi "<<this->ID<<endl;
    user_manager_interface.setAccount(ID);

    cout<<"rec   id   get"<<ID<<endl;

    //ui->testLayout= new QVBoxLayout;

   ui->testLayout->removeItem(pageTable);


    QStringList header;
    header<<"预览图"<<"书名"<<"作者"<<"出版社"<<"出版时间"<<"ISBN"<<"分区"<<"总收藏数";
    pageTable = new PageTable(header, 5);
    ui->testLayout->addLayout(pageTable);

    connect(pageTable->pageWidget, SIGNAL(currentPageChanged(int)), this, SLOT(PageChange(int)));

    //connect(ui->search_widget,SIGNAL(text_to_interface(QString)), this, SLOT(text_from_interface(QString)));

    //利用search_btn_clicked信号加载数据，
    connect(ui->search_widget,SIGNAL(search_btn_clicked(QString,int)),this,SLOT(BtnLoadDataClick(QString,int)));

    //qDebug() << "main: " << search_text;

    connect(pageTable,SIGNAL(item_is_clicked(QString)),this,SLOT(items_clicked(QString)));

}

void Manager_Interface::items_clicked(QString isbn_clicked)
{
    emit item_clicked(isbn_clicked, user_manager_interface);
}


//void Manager_Interface::text_from_interface(QString str)
//{
//    search_text = str;
//    qDebug() << "interface：" << search_text;
//}

void Manager_Interface::LoadPage(int pageIndex, vector<Book> bk_temp){

    DataList3.clear();//先清空，只缓存一页。如果有100万条，缓存到List不合适
//    int sz = result_select.size();

    pageTable->clear_contents();
    qDebug() << page_num << "SSSS" << bk_temp.size();

    int bas = (pageIndex - 1) * 5;
    for(int i = bas;i < min((int)bk_temp.size(), bas + 5);i++){//10行
        Book bk = bk_temp[i];
        QList<QString> Row;
        RowIndex3 += 1;
        Row.append(QString::fromLocal8Bit(bk.getImage()));
        Row.append(QString::fromLocal8Bit(bk.getName()));
        Row.append(QString::fromLocal8Bit(bk.getAuthor()));
        Row.append(QString::fromLocal8Bit(bk.getPublisher()));
        Row.append(QString::fromLocal8Bit(bk.getPublishDate()));
        Row.append(QString::fromLocal8Bit(bk.getIsbn()));
        Row.append(QString::fromLocal8Bit(bk.getClassifition()));
        Row.append(QString::number(bk.getNumMark()));
        DataList3.append(Row);
    }
    pageTable->SetData(DataList3);
}

void Manager_Interface::BtnLoadDataClick(QString str,int search_kind){

    has_selected = 1;
    result_select.clear();
    search_text = str;

    QByteArray ba=search_text.toLocal8Bit();
    char *c=ba.data();

    if(search_kind & 1)
    {
        search_temp.clear();
        if(mUtils2.GetBooksByBookName(c,search_temp))
        {
            qDebug() << "qdebug";
            result_select = search_temp;
        }
        else
        {
            qDebug() << "false";
        }
    }
    if(search_kind >> 1 & 1)
    {
        search_temp.clear();
        if(mUtils2.GetBooksByAuthor(c,search_temp))
        {
            qDebug() << "qdebug";
            int flag = 0;
            for(int i = 0; i < (int)search_temp.size(); i++)
            {
                flag = 0;
                for(int j = 0; j < (int)result_select.size(); j++)
                {
                    if(!strcmp(search_temp[i].getIsbn(), result_select[j].getIsbn()))
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0)
                {
                    result_select.push_back(search_temp[i]);
                }
            }
        }
        else
        {
            qDebug() << "false";
        }
    }
    if(search_kind >> 2 & 1)
    {
        search_temp.clear();
        Book bk_test;
        bk_test.setIsbn(c);
        if(mUtils2.CheckBookExist(bk_test))
        {
            qDebug() << "qdebug";
            result_select = search_temp;

            bk_test = mUtils2.GetBookByIsbn(c);

            int flag = 0;
            for(int i = 0; i < (int)result_select.size(); i++)
            {
                if(!strcmp(result_select[i].getIsbn(), bk_test.getIsbn()))
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
            {
                result_select.push_back(bk_test);
            }
        }
        else
        {
            qDebug() << "false";
        }
    }
    if(search_kind >> 3 & 1)
    {
        search_temp.clear();

        int id = -1;
        for(int i = 0 ; i < 22; i++)
        {
            if(mp[i] == search_text.toStdString())
            {
                id = i;
                break;
            }
        }
        if(id != -1)
        {

            qDebug() << "分区搜索成功" << id;
            if(mUtils2.GetBooksByClassificationId(id,search_temp))
            {
                qDebug() << "qdebug";
                int flag = 0;
                for(int i = 0; i < (int)search_temp.size(); i++)
                {
                    flag = 0;
                    for(int j = 0; j < (int)result_select.size(); j++)
                    {
                        if(!strcmp(search_temp[i].getIsbn(), result_select[j].getIsbn()))
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 0)
                    {
                        result_select.push_back(search_temp[i]);
                    }
                }
            }
            else
            {
                qDebug() << "false";
            }
        }

    }

    page_num = (result_select.size() + 4) / 5;


    qDebug() << "click ...."<<RowIndex3;
    pageTable->pageWidget->setMaxPage(page_num);//假如有10页数据
    pageTable->pageWidget->setCurrentPage(1);

    RowIndex3 = 0;
    LoadPage(1, result_select);//加载第一页

}

void Manager_Interface::PageChange(int currentPage){

    qDebug()<<"pageChagne"<<currentPage;
    if(has_selected == 1)
    {
        this->LoadPage(currentPage, result_select);
    }
    else
    {
        this->LoadPage(currentPage, recommod_list);
    }
}


Manager_Interface::~Manager_Interface()
{
    delete ui;
}


void Manager_Interface::on_pushButton_clicked()
{
    qDebug() << "推荐列表之前";
    //加载推荐列表

    pageTable->clear_contents();

    mUtils2.UpdateMarkRank();
    mUtils2.UpdateBorrowRank();
    recommod_list.clear();
    cout<<user_manager_interface.getAccount()<<"   abababa"<<endl;
    if(mUtils2.UpdateRecommandList(user_manager_interface))
    {
        qDebug() << "更新推荐列表成功！";
        if(mUtils2.GetRecommendList(user_manager_interface, recommod_list))
        {
            qDebug() << "加载推荐列表成功";
            vector<Book> bk_list2;
            for(int i = 0; i < recommod_list.size(); i++)
            {
                int flag = 0;
                for(int j = 0; j < bk_list2.size(); j++)
                {
                    if(!strcmp(bk_list2[j].getIsbn(),recommod_list[i].getIsbn()))
                    {
                        flag = 1;
                    }
                }
                if(flag == 0)
                {
                    bk_list2.push_back(recommod_list[i]);
                }
            }
            cout<<bk_list2.size()<<" list size of rec"<<endl;
            LoadPage(1,bk_list2);

        }
        else
        {
            qDebug() << "加载推荐列表失败";
        }
    }
    else
    {
        qDebug() << "更新推荐列表失败！";
    }
}
