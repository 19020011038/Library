#ifndef COLLECTION_H
#define COLLECTION_H

#include <QMainWindow>

#include <config.h>
//#include<QTableView>

namespace Ui {
class Collection;
}

class Collection : public QMainWindow
{
    Q_OBJECT

public:
    explicit Collection(QWidget *parent = 0);
    ~Collection();
    void setID(char *id);

private slots:
    void on_pushButton_return_clicked();
    void delete_favour();//取消该本书的点赞
    void get_bookdetail(char *ISBN);
    void get_collection_book(char* student_id);//得到该学号对应的收藏书籍



signals:
    void send_collect_returnSignal();

private:
    Ui::Collection *ui;
    char ID[ACCOUNT_SIZE];
};

#endif // COLLECTION_H
