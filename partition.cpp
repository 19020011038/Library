#include "partition.h"
#include "ui_partition.h"
#include <QPushButton>
#include <qDebug>
#include <unordered_map>
#include "tool.h"

unordered_map<int,QString> mp;
User user_from_main;

Partition::Partition(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Partition)
{
    ui->setupUi(this);

    load_page = new LoadPage;
    mp.insert({0,"1.哲学"});
    mp.insert({1,"2.人文社科综合"});
    mp.insert({2,"3.管理学"});
    mp.insert({3,"4.政治"});
    mp.insert({4,"5.法律"});
    mp.insert({5,"6.经济"});
    mp.insert({6,"7.文化/教育"});
    mp.insert({7,"8.语言/文学"});
    mp.insert({8,"9.艺术"});
    mp.insert({9,"10.历史"});
    mp.insert({10,"11.数学"});
    mp.insert({11,"12.物理"});
    mp.insert({12,"13.化学/材料"});
    mp.insert({13,"14.理工综合"});
    mp.insert({14,"15.地球科学"});
    mp.insert({15,"16.生物"});
    mp.insert({16,"17.医学/药学"});
    mp.insert({17,"18.农业/水产"});
    mp.insert({18,"19.工业技术"});
    mp.insert({19,"20.计算机/网络"});
    mp.insert({20,"21.环境"});
    mp.insert({21,"22.其它"});

    for(int i = 0; i <= 21; i++)
    {
        QListWidgetItem * q = new QListWidgetItem;
        q->setText(mp[i]);
        ui->listWidget->addItem(q);
    }

    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(listwidget_clicked_to_main(QListWidgetItem*)));
    //qDebug() << "分区号" ;
}

//Utils mUtils = Utils();

void Partition::on_pushButton_return_clicked()
{
    emit sendsignal();
    this->close();
}

void Partition::get_info(char *id)
{
    setID(id);
    Utils mutils = Utils();
    user_from_main= mutils.GetUser(id);
}


void Partition::listwidget_clicked_to_main(QListWidgetItem * item)
{
    //寻找到当前item的分区号
    int id = 0;

    QString str = item->text();
    QString temp = "";
    int i = 0;
    while(i < str.size() && (str[i] >= '0' && str[i] <= '9'))
    {
        temp += str[i];
        i++;
    }
    id = temp.toInt();

    //qDebug() << "分区号" << id;
    //将分区号，用signal发送到main。
    //cout<<user_from_main.getAccount()<<endl;

    emit listwidget_clicked(id-1, user_from_main);

    //load_page->show();

}

void Partition::Show_Partitionpage()
{
    this->show();
}

Partition::~Partition()
{
    delete ui;
}

//void Partition::on_btnskip_clicked()
//{
//    this->hide();
//    emit Loadage_signal();
//}
