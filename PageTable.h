#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <QVBoxLayout>
#include <QTableWidget>
#include "PageWidget.h"
#include <QList>
#include "book.h"

class PageTable: public QVBoxLayout
{
    Q_OBJECT
public:
    PageTable(QStringList &header,int rowCount = 10);
    void SetData(QList<QList<QString>> &DataList);
    ~PageTable();

    void clear_contents();

private:

public slots:
    void item_clicked_signal_to_bookrank(int row, int col);

signals:
    void item_is_clicked(QString clicked_isbn);

public:
    int PageSize = 10;
    PageWidget *pageWidget;
    QTableWidget *tableWidget;

};

#endif // PAGETABLE_H
