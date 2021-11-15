#include "PageT.h"
#include <QTableWidget>
#include <QDebug>
#include <QObject>
#include <QHeaderView>
#include <book.h>
#include <QPushButton>
#include <tool.h>
#include <QMessageBox>
#include <add_book.h>
#include <modify_book.h>


PageT::PageT(QStringList &header,int rowCount)
{
    qDebug()<<" PageT init ,rowCount:"<<rowCount << ",header size:"<<header.size();

    tableWidget = new QTableWidget(rowCount,header.size());//构造一个10行5列的表格
    tableWidget->setWindowTitle("Title");

    for(int i = 0; i < rowCount; i++)
    {
        tableWidget->setRowHeight(i, 60);
    }

    //tableWidget->setRowHeight(1,20);
    tableWidget->setHorizontalHeaderLabels(header);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//设置表格为单行选择
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置只能选中行，不能单个选择单元格
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置单元格不可编辑

    tableWidget->verticalHeader()->setHidden(true);// 隐藏行号 (不显示前面行号)
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//让表格挤满占个父容器
//    for(int i = 1;i<header.size();i++)
//        tableWidget->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Interactive);   //然后设置要根据内容使用宽度的列（其他没设置的列自动缩放）


//    for(int i = 0;i<rowCount;i++){
//        tableWidget->setItem(i,0, new QTableWidgetItem("context"));
//        tableWidget->item(i,0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
//        tableWidget->setRowHeight(i,25);
//    }

    //设置表头样式
    tableWidget->setStyleSheet("QHeaderView::section {"
                               "color: black;font:bold 14px \"微软雅黑\";"
                               "text-align:center;"
                               "height:25px;"
                               "background-color: #d1dff0;"
                               " border:1px solid #8faac9;"
                               "border-left:none;"
                               "}");

    QHBoxLayout *hLayout = new QHBoxLayout();//让PageWidget水平居中
    pageWidget = new PageWidget();
    //pageWidget->setMaxPage(20);
    hLayout->addWidget(pageWidget);

    // 分页组件的css,这个内容应该放到普通文件中然后加载
    QString qss = QString(".QLabel[page=\"true\"] { padding: 1px; }")
            + QString(".QLabel[currentPage=\"true\"] { color: rgb(190, 0, 0);}")
            + QString(".QLabel[page=\"true\"]:hover { color: white; border-radius: 4px; background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(53, 121, 238, 255), stop:1 rgba(0, 202, 237, 255));}");
    pageWidget->setStyleSheet(qss);


    this->addWidget(tableWidget);
    this->addLayout(hLayout);

    tableWidget->horizontalHeader()->size();//列

    QObject::connect(tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(item_clicked_signal_to_bookrank(int, int)));

}

void PageT::SetData(QList<QList<QString>> &DataList)
{
   this->tableWidget->clearContents();
   for(int i = 0;i<DataList.size();i++){

        QList<QString> Item = DataList[i];
        for(int j = 0;j<Item.size();j++){
            this->tableWidget->setItem(i,j, new QTableWidgetItem(Item[j]));
        }
        QPushButton *delete_book_button = new QPushButton("删除图书");

        delete_book_button->setProperty("isbn",DataList[i][5]);
        delete_book_button->setProperty("status","normal");
        //qDebug()<<"shu"<<DataList[i][5]<<endl;
        connect(delete_book_button,SIGNAL(clicked()),this,SLOT(delete_book()));
        this->tableWidget->setCellWidget(i,Item.size(),delete_book_button);



        QPushButton *modify_book_button = new QPushButton("修改图书");
        modify_book_button->setProperty("isbn",DataList[i][5]);
        modify_book_button->setProperty("status","normal");
        connect(modify_book_button,SIGNAL(clicked()),this,SLOT(change_book()));
        this->tableWidget->setCellWidget(i,Item.size()+1,modify_book_button);


        QPushButton *add_book_button = new QPushButton("修改数量");
        add_book_button->setProperty("isbn",DataList[i][5]);
        add_book_button->setProperty("status","normal");
        connect(add_book_button,SIGNAL(clicked()),this,SLOT(add_book()));
        this->tableWidget->setCellWidget(i,Item.size()+2,add_book_button);


        //connect
   }

}

void PageT::delete_book()
{
    Utils mutils =Utils();

    QPushButton *button=(QPushButton*)sender();


    QString str1 = button->property("isbn").toString();
    //qDebug()<<"str"<<str1<<endl;
    QByteArray ba = str1.toLocal8Bit();
    char *c_str2 = ba.data();
    //cout<<"c_str"<<c_str2<<endl;

    Book book = mutils.GetBook(c_str2);

    if(mutils.RemoveBook(book)==false)
    {
        QMessageBox msgBox;
        msgBox.setText("删除失败");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("删除成功");
        msgBox.exec();
    }
}

void PageT::add_book()
{
    Add_Book *add_book=new Add_Book;

    QPushButton *button=(QPushButton*)sender();

    QString str1 = button->property("isbn").toString();
    //qDebug()<<"str"<<str1<<endl;
    QByteArray ba = str1.toLocal8Bit();
    char *c_str2 = ba.data();

    add_book->setIsbn(c_str2);
    add_book->show();

}

void PageT::change_book()
{
    modify_book *modify = new modify_book;
    QPushButton *button=(QPushButton*)sender();

    QString str1 = button->property("isbn").toString();
    //qDebug()<<"str"<<str1<<endl;
    QByteArray ba = str1.toLocal8Bit();
    char *c_str2 = ba.data();

    modify->get_book_info(c_str2);

    modify->show();
}


void PageT::item_clicked_signal_to_bookrank(int row, int col)
{
    //qDebug() << "success";
    QTableWidgetItem * qtablewidgetitem = tableWidget->item(row, 5);
    if(qtablewidgetitem == nullptr)
    {
        //qDebug() << "item_clicked_false";
    }
    else
    {
        //qDebug() << "row : " << row << "col : " << col;
        QString isbn_click = qtablewidgetitem->text();
        //qDebug() << "isbn_clicked : " << isbn_click;
        emit this->item_is_clicked(isbn_click);
    }
}


PageT::~PageT()
{
    qDebug() << "~PageT() invoke..." ;
}
