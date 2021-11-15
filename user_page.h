#ifndef USER_PAGE_H
#define USER_PAGE_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTableWidget>
#include "PageWidget.h"
#include <QList>
#include "user.h"

class user_page : public QVBoxLayout
{
    Q_OBJECT

public:
    explicit user_page(QStringList &header,int rowCount = 10);
    void SetData(QList<QList<QString>> &DataList);
    ~user_page();
    int PageSize = 10;
    PageWidget *pageWidget;
    QTableWidget *tableWidget;

public slots:
    void item_clicked_signal_to_bookrank(int row, int col);
    void delete_user();
    void change_user();


signals:
    void item_is_clicked(QString clicked_isbn);


};

#endif // USER_PAGE_H
