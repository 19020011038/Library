#ifndef PageT_H
#define PageT_H

#include <QVBoxLayout>
#include <QTableWidget>
#include "PageWidget.h"
#include <QList>
#include "book.h"

class PageT: public QVBoxLayout
{
    Q_OBJECT
public:
    PageT(QStringList &header,int rowCount = 10);
    void SetData(QList<QList<QString>> &DataList);
    ~PageT();
private:

public slots:
    void item_clicked_signal_to_bookrank(int row, int col);
    void delete_book();
    void change_book();
    void add_book();

signals:
    void item_is_clicked(QString clicked_isbn);

public:
    int PageSize = 10;
    PageWidget *pageWidget;
    QTableWidget *tableWidget;

};

#endif // PageT_H
