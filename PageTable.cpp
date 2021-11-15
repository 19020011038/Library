#include "PageTable.h"
#include <QTableWidget>
#include <QDebug>
#include <QObject>
#include <QHeaderView>
#include <book.h>


PageTable::PageTable(QStringList &header,int rowCount)
{


    //qDebug()<<" PageTable init ,rowCount:"<<rowCount << ",header size:"<<header.size();

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

void PageTable::clear_contents()
{
    this->tableWidget->clearContents();
}

void PageTable::SetData(QList<QList<QString>> &DataList)
{
   this->tableWidget->clearContents();
   for(int i = 0;i<DataList.size();i++){

        QList<QString> Item = DataList[i];
        for(int j = 0;j<Item.size();j++){
            this->tableWidget->setItem(i,j, new QTableWidgetItem(Item[j]));
        }
   }
}

void PageTable::item_clicked_signal_to_bookrank(int row, int col)
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


PageTable::~PageTable()
{
    //qDebug() << "~PageTable() invoke..." ;
}
