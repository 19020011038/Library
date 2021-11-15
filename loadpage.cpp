#include "loadpage.h"
#include "ui_loadpage.h"
#include "tool.h"
#include <vector>
#include <QDebug>
#include "book.h"

vector<Book> result_partition;
int page_num_2;
Utils mUtils5 = Utils();
User user_partition;

LoadPage::LoadPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadPage)
{
    ui->setupUi(this);

    //qDebug() << "[Debug] MyObject::test ";

    //表格不是直接用UI写的，是new出来的。
    //文件结构上 PageWidget 是 在PageTable对象中的。
    QStringList header;
    header<<"预览图"<<"书名"<<"作者"<<"出版社"<<"出版时间"<<"ISBN"<<"总收藏数";
    pageTable = new PageTable(header, 5);
    ui->testLayout->addLayout(pageTable);
    //pageTable2 = new PageTable(header, 5);
    //ui->testLayout2->addLayout(pageTable2);

    connect(pageTable->pageWidget, SIGNAL(currentPageChanged(int)), this, SLOT(PageChange(int)));
    //connect(pageTable2->pageWidget, SIGNAL(currentPageChanged(int)), this, SLOT(PageChange2(int)));
    //connect(ui->btnLoadData, &QPushButton::clicked, this, SLOT(BtnLoadDataClick()));

    connect(pageTable, SIGNAL(item_is_clicked(QString)), this, SLOT(ISBN_to_main_slot(QString)));

    connect(ui->btnLoadData,&QPushButton::clicked,[=](){
            BtnLoadDataClick();
        });

}

void LoadPage::ISBN_to_main_slot(QString isbn_str)
{
    //user_partition.setAccount("19020011038");
    emit ISBN_to_main_SIGNAL(isbn_str, user_partition);
}


void LoadPage::Show_Loadpage(int id, User user_from_partition)
{
    user_partition = user_from_partition;
    //cout<<"dsassasa"<<user_partition.getAccount()<<endl;

    //qDebug() << "pause" << id;
    result_partition.clear();
    pageTable->clear_contents();
    if(Utils().GetBooksByClassificationId(id, result_partition))
    {
        //qDebug() << "该分区内书籍 : " << result_partition.size();
        page_num_2 = (result_partition.size() + 4) / 5;
    }
    else
    {
        //qDebug() << "通过分区号搜索书籍失败";
    }

    this->show();
}

void LoadPage::on_pushButton_2_clicked()
{
    this->hide();
    emit Partitionpage();
}

QList<QList<QString>> DataList;//数据
int RowIndex = 0;

void LoadPage::LoadPagee(int pageIndex){

    DataList.clear();//先清空，只缓存一页。如果有100万条，缓存到List不合适



    int bas = (pageIndex - 1) * 5;
    for(int i = bas; i < min(bas + 5, (int)result_partition.size()); i++){//10行
        Book bk = result_partition[i];
        QList<QString> Row;
        RowIndex += 1;
        Row.append(QString::fromLocal8Bit(bk.getImage()));
        Row.append(QString::fromLocal8Bit(bk.getName()));
        Row.append(QString::fromLocal8Bit(bk.getAuthor()));
        Row.append(QString::fromLocal8Bit(bk.getPublisher()));
        Row.append(QString::fromLocal8Bit(bk.getPublishDate()));
        Row.append(QString::fromLocal8Bit(bk.getIsbn()));
        Row.append(QString::number(bk.getNumMark()));
        DataList.append(Row);
    }
    pageTable->SetData(DataList);
}

void LoadPage::BtnLoadDataClick(){

    //qDebug() << "click ...."<<RowIndex;
    pageTable->pageWidget->setMaxPage(page_num_2);//假如有10页数据
    pageTable->pageWidget->setCurrentPage(1);

    RowIndex = 0;
    LoadPagee(1);//加载第一页

}


void LoadPage::PageChange(int currentPage){

    //qDebug()<<"pageChagne"<<currentPage;
    this->LoadPagee(currentPage);
}

LoadPage::~LoadPage()
{

    delete ui;
}


