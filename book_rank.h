#ifndef BOOK_RANK_H
#define BOOK_RANK_H

#include <QMainWindow>
#include "PageWidget.h"
#include "PageTable.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Book_Rank;
}
QT_END_NAMESPACE

class Book_Rank : public QMainWindow
{
    Q_OBJECT

public:
    Book_Rank(QWidget *parent = 0);
    ~Book_Rank();

//自定义槽函数
public slots:
    void BtnLoadDataClick();
    void PageChange(int currentPage);
    void PageChange2(int currentPage);

    void items_clicked(QString isbn_clicked);
    void on_pushButton_return_clicked();

signals:
    void item_clicked(QString isbn_clicked, User user_now);
    void sendSignal();

private:
    Ui::Book_Rank *ui;
    PageWidget *pageWidget;
    PageTable *pageTable;
    PageTable *pageTable2;

    void LoadPage(int pageIndex);
    void LoadPage2(int pageIndex);
};
#endif // BOOK_RANK_H
