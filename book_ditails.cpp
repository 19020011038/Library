#include "book_ditails.h"
#include "ui_book_ditails.h"
#include <QStringList>
#include <QDebug>
#include "tool.h"
#include "user.h"
#include "isbn-book_id.h"
#include <PageTable.h>
#include <QMessageBox>

Utils mUtils3 = Utils();
Book book_clicked;
User user_select;
vector<IsbnBookId> vector_isbnbookid;

Book_Ditails::Book_Ditails(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Book_Ditails)
{
    ui->setupUi(this);

    QStringList header;
    header<<"序号"<<"书刊状态"<<"借阅";

    //自动添加滑轮，不需单独设置
    int nColCouunt = header.size();
    ui->table_list->setColumnCount(nColCouunt);
    ui->table_list->setHorizontalHeaderLabels(header);
    ui->table_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//让表格挤满占个父容器
    ui->table_list->setSelectionMode(QAbstractItemView::SingleSelection);//设置表格为单行选择
    ui->table_list->setSelectionBehavior(QAbstractItemView::SelectRows);//设置只能选中行，不能单个选择单元格
    ui->table_list->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置单元格不可编辑
    ui->table_list->setStyleSheet("QHeaderView::section {"
                               "color: black;font:bold 14px \"微软雅黑\";"
                               "text-align:center;"
                               "height:25px;"
                               "background-color: #d1dff0;"
                               " border:1px solid #8faac9;"
                               "border-left:none;"
                               "}");

    ui->table_list->verticalHeader()->setHidden(true);// 隐藏行号 (不显示前面行号)
    this->LoadPage();


    connect(ui->table_list, SIGNAL(cellClicked(int, int)),this,SLOT(judge_borrow(int, int)));

    connect(ui->widget, SIGNAL(btn_mark_clicked()), this, SLOT(mark_book_detail()));
    connect(ui->widget, SIGNAL(btn_appoint_clicked()), this, SLOT(appoint_book_detail()));

    //this->show();
}

void Book_Ditails::judge_borrow(int row, int col)
{
    //qDebug() << "已经进入借阅槽函数了";
    if(col == 2)
    {
        QTableWidgetItem * qtablewidgetitem = ui->table_list->item(row, 0);
        if(qtablewidgetitem == nullptr)
        {
            //qDebug() << "item_clicked_false";
        }
        else
        {
            //qDebug() << "row : " << row << "col : " << col;
            QString id_click = qtablewidgetitem->text();
            int id_select = id_click.toInt();
            //qDebug() << "id_clicked : " << id_click;

            if(book_clicked.getLeft() == 0)
            {
                QMessageBox msgBox;
                msgBox.setText("借阅失败，无剩余书籍！");
                msgBox.exec();

            }
            else if(book_clicked.getLeft() == 1)
            {
                if(mUtils3.CheckIfBookAppointed(book_clicked))
                {
                    User appoint_user = mUtils3.GetAppointmentUser(book_clicked);
                    if(appoint_user.getId() == user_select.getId())
                    {
                        if(mUtils3.CheckIfBookIdBorrowed(book_clicked, id_select))
                        {
                            QMessageBox msgBox;
                            msgBox.setText("所选这本已经被借阅了！");
                            msgBox.exec();

                        }
                        else
                        {
                            //直接借阅
                            if(mUtils3.Borrow(user_select, book_clicked, id_select))
                            {
                                QMessageBox msgBox;
                                msgBox.setText("借阅成功！");
                                msgBox.exec();
                                this->close();
                            }
                            else
                            {
                                QMessageBox msgBox;
                                msgBox.setText("借阅失败！");
                                msgBox.exec();

                            }
                        }
                    }
                    else
                    {
                        QMessageBox msgBox;
                        msgBox.setText("这本书已经被预约了！");
                        msgBox.exec();

                    }
                }
                else
                {
                    if(mUtils3.CheckIfBookIdBorrowed(book_clicked, id_select))
                    {
                        QMessageBox msgBox;
                        msgBox.setText("所选这本已经被借阅了！");
                        msgBox.exec();

                    }
                    else
                    {
                        //直接借阅
                        if(mUtils3.Borrow(user_select, book_clicked, id_select))
                        {
                            QMessageBox msgBox;
                            msgBox.setText("借阅成功！");
                            msgBox.exec();
                            this->close();
                        }
                        else
                        {
                            QMessageBox msgBox;
                            msgBox.setText("借阅失败！");
                            msgBox.exec();

                        }
                    }
                }
            }
            else
            {
                if(mUtils3.CheckIfBookIdBorrowed(book_clicked, id_select))
                {
                    QMessageBox msgBox;
                    msgBox.setText("所选这本已经被借阅了！");
                    msgBox.exec();

                }
                else
                {
                    //直接借阅
                    if(mUtils3.Borrow(user_select, book_clicked, id_select))
                    {
                        QMessageBox msgBox;
                        msgBox.setText("借阅成功！");
                        msgBox.exec();
                        this->close();
                        qDebug() << "借阅后，剩余书籍量：" << book_clicked.getLeft();
                        vector<IsbnBookId> vector_new;
                        if(mUtils3.GetBookIdsOfBook(book_clicked,vector_new))
                        {
                            qDebug() << "借阅之后，vector.size 为：" << vector_new.size();
                        }
                    }
                    else
                    {
                        QMessageBox msgBox;
                        msgBox.setText("借阅失败！");
                        msgBox.exec();

                    }
                }
            }

        }

    }

}

void Book_Ditails::mark_book_detail()
{
    //qDebug() << "mark_book_detail";
    //qDebug() << "Book Mark User: " << user_select.getName();
    //qDebug() << "已经进入收藏槽函数了";
    vector<Book> mark_list;
    int flag = 0;
    mUtils3.GetMarkList(user_select, mark_list);
    //qDebug() << "收藏人数：            " << mark_list.size();
    for(int i = 0; i < mark_list.size(); i++)
    {
        //qDebug() << mark_list[i].getName();
        //qDebug() << "收藏列表中的书籍" << mark_list[i].getIsbn();
        //qDebug() << "被点击的书籍" << book_clicked.getIsbn();
        if(!strcmp(mark_list[i].getIsbn(),book_clicked.getIsbn()))
        {
            flag = 1;
            break;
        }
    }
    if(flag == 1)
    {
        QMessageBox msgBox;
        msgBox.setText("当前用户已经收藏！");
        msgBox.exec();

    }
    else
    {

        if(mUtils3.SetMark(user_select, book_clicked, 1))
        {
            //qDebug() << "setMark_success";
            QMessageBox msgBox;
            msgBox.setText("收藏成功！");
            msgBox.exec();

        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("收藏失败！");
            msgBox.exec();

            //qDebug() << "setMark_false";
        }
    }

}

void Book_Ditails::appoint_book_detail()
{
    //qDebug() << "appoint_book_detail";
    //qDebug() << "已经进入预约槽函数了";
    if(mUtils3.CheckIfBookAppointed(book_clicked))
    {
        QMessageBox msgBox;
        msgBox.setText("该书已经被预约！");
        msgBox.exec();

    }
    else
    {
        cout<<"bool_clickedasdsaas"<<book_clicked.getIsbn()<<endl;
        cout<<"bool_leftasdsadsaas"<<book_clicked.getLeft()<<endl;
        if(book_clicked.getLeft() > 0)
        {
            //qDebug() << "剩余书籍量：" << book_clicked.getLeft();
            QMessageBox msgBox;
            msgBox.setText("该书仍有剩余，无法预约！");
            msgBox.exec();

        }
        else
        {
            mUtils3.Appoint(user_select, book_clicked);
            QMessageBox msgBox;
            msgBox.setText("预约成功！");
            msgBox.exec();

        }
    }

//    //qDebug() << "Book Mark User: " << user_select.getName();

//    if(mUtils3.Borrow(user_select, book_clicked, ))
//    {
//        //qDebug() << "setMark_success";
//    }
//    else
//    {
//        //qDebug() << "setMark_false";
//    }
}

void Book_Ditails::show_bookditals(QString isbn_clicked, User user_now)
{
    QByteArray ba=isbn_clicked.toLocal8Bit();
    char *c=ba.data();

    user_select = user_now;


    book_clicked = mUtils3.GetBookByIsbn(c);

    QString set_str;

    set_str = QString::fromLocal8Bit(book_clicked.getName());
    ui->widget->set_book_name(set_str);

    set_str = QString::fromLocal8Bit(book_clicked.getAuthor());
    ui->widget->set_book_author(set_str);

    set_str = QString::fromLocal8Bit(book_clicked.getPublisher());
    ui->widget->set_book_publisher(set_str);

    set_str = QString::fromLocal8Bit(book_clicked.getPublishDate());
    ui->widget->set_book_publish_time(set_str);

    set_str = QString::number(book_clicked.getNumBorrow());
    ui->widget->set_book_borrownumber(set_str);

    set_str = QString::number(book_clicked.getNumMark());
    ui->widget->set_book_marknumber(set_str);

    set_str = QString::number(book_clicked.getPrice(),'f',2);
    ui->widget->set_book_price(set_str);

    set_str = QString::number(book_clicked.getLeft());
    ui->widget->set_book_leftnumber(set_str);

    set_str = QString::number(book_clicked.getStorage());
    ui->widget->set_book_storagenumber(set_str);

    set_str = QString::fromLocal8Bit(book_clicked.getDescription());
    ui->widget->set_book_discription(set_str);

    set_str = QString::fromLocal8Bit(book_clicked.getImage());
    ui->widget->set_book_photo(set_str);

//    //设置图片
//    set_str = QString::fromUtf8(book_clicked.getName());
//    ui->widget->set_book_name(set_str);

    vector_isbnbookid.clear();
    ui->table_list->clearContents();
    ui->table_list->setRowCount(0);
    //qDebug() << "rowCount :" << ui->table_list->rowCount();
    //qDebug() << "test__";
    if(mUtils3.GetBookIdsOfBook(book_clicked,vector_isbnbookid))
    {
         for(int i = 0; i < vector_isbnbookid.size(); i++)
         {
             cout << vector_isbnbookid[i].getBookId() << endl;
         }
         //qDebug() << "book_details_loadpage:                             " << (int)vector_isbnbookid.size();
         for(int i = 0; i < (int)vector_isbnbookid.size(); i++)
         {
             //添加新行
             ui->table_list->insertRow(ui->table_list->rowCount());
             int rowIdx = ui->table_list->rowCount()-1;
             //必须先设置item,然后再获取,因为默认是空的
             QString str = QString::number(vector_isbnbookid[i].getBookId());
             //qDebug() << str;
             QTableWidgetItem *item_id = new QTableWidgetItem(str);
             int book_state = vector_isbnbookid[i].getIsBorrowed();
             QTableWidgetItem *item_state = new QTableWidgetItem(book_state == 1 ? "已被借阅" : "尚未借阅");
             QTableWidgetItem *item_borrow = new QTableWidgetItem("单击此处借阅");
             ui->table_list->setItem(rowIdx,0,item_id);
             ui->table_list->setItem(rowIdx,1,item_state);
             ui->table_list->setItem(rowIdx,2,item_borrow);
         }
    }
    else
    {
        //qDebug() << "book_details_loadpage_false ";
    }


    this->show();
}

//QList<QList<QString>> DataList1;//数据
int RowIndex_bookditail = 0;

void Book_Ditails::LoadPage(){



//    for(int i = 0; i < (int)vector_isbnbookid.size(); i++)
//    {
//        //添加新行
//        ui->table_list->insertRow(ui->table_list->rowCount());
//        int rowIdx = ui->table_list->rowCount()-1;
//        //必须先设置item,然后再获取,因为默认是空的
//        QString str = QString::number(vector_isbnbookid[i].getId());
//        QTableWidgetItem *item_id = new QTableWidgetItem(str);
//        int book_state = vector_isbnbookid[i].getIsBorrowed();
//        QTableWidgetItem *item_state = new QTableWidgetItem(book_state == 1 ? "已被借阅" : "尚未借阅");
//        QTableWidgetItem *item_borrow = new QTableWidgetItem(str);
//        ui->table_list->setItem(rowIdx,0,item_id);
//        ui->table_list->setItem(rowIdx,1,item_state);
//        ui->table_list->setItem(rowIdx,2,item_borrow);
//    }

    //objs是已经读取好的数据
//    for(int i = 0; i < 10; i++){
//         //SysUser obj = objs[i];
//         //添加新行
//         ui->table_list->insertRow(ui->table_list->rowCount());
//         int rowIdx = ui->table_list->rowCount()-1;
//         //必须先设置item,然后再获取,因为默认是空的
//         QTableWidgetItem *item0 = new QTableWidgetItem(0);
//         QTableWidgetItem *item1 = new QTableWidgetItem(0);
//         QTableWidgetItem *item2 = new QTableWidgetItem(0);
//         ui->table_list->setItem(rowIdx,0,item0);
//         ui->table_list->setItem(rowIdx,1,item1);
//         ui->table_list->setItem(rowIdx,2,item2);
//    }
}

Book_Ditails::~Book_Ditails()
{
    delete ui;
}

