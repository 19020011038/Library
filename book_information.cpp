#include "book_information.h"
#include "ui_book_information.h"
#include <QLabel>
#include <QMovie>
#include <QImage>
#include <QDebug>
#include <QPixmap>

Book_Information::Book_Information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Book_Information)
{
    ui->setupUi(this);



    connect(ui->apoint_book, SIGNAL(clicked()), this, SLOT(appoint_clicked()));
    connect(ui->mark_book, SIGNAL(clicked()), this, SLOT(mark_clicked()));

    //ui->photo->show();
}

void Book_Information::mark_clicked()
{
    emit btn_mark_clicked();
    //qDebug() << "mark_clicked";
}

void Book_Information::appoint_clicked()
{
    emit btn_appoint_clicked();
}

void Book_Information::set_book_name(QString str)
{
    ui->book_name->setText("书名："+str);
}

void Book_Information::set_book_author(QString str)
{
    ui->writer->setText("作者："+str);
}

void Book_Information::set_book_publisher(QString str)
{
    ui->publisher->setText("出版社："+str);
}

void Book_Information::set_book_publish_time(QString str)
{
    ui->publish_time->setText("出版时间："+str);
}

void Book_Information::set_book_borrownumber(QString str)
{
    ui->borrow_number->setText("借阅量："+str);
}

void Book_Information::set_book_price(QString str)
{
    ui->price->setText("价格："+str);
}

void Book_Information::set_book_marknumber(QString str)
{
    ui->collection_number->setText("收藏量："+str);
}

void Book_Information::set_book_storagenumber(QString str)
{
    ui->storage_number->setText("库存数量："+str);
}

void Book_Information::set_book_leftnumber(QString str)
{
    ui->left_number->setText("剩余数量："+str);
}

void Book_Information::set_book_discription(QString str)
{
    ui->description->setText("详细描述："+str);
    ui->description->setWordWrap(true);
}

void Book_Information::set_book_photo(QString str)
{
    //直接调用QString读入。

    QString tem = "C://Users/yyx/Desktop/Library/image/";

    tem=tem+str+".jpg";
    qDebug()<<"imagesadsaaadsas"<<tem;
    QImage *image = new QImage(tem);
    QImage *imgscaled = new QImage;
    *imgscaled = image->scaled(180,240);
    //image->scaled(50, 20);

    ui->photo->setPixmap(QPixmap::fromImage(*imgscaled));

}

Book_Information::~Book_Information()
{
    delete ui;
}
