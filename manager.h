#ifndef manager_H
#define manager_H

#include <QWidget>
#include "PageT.h"
#include "PageWidget.h"
#include "user.h"
#include "book_addonly.h"

QT_BEGIN_NAMESPACE
namespace Ui { class manager; }
QT_END_NAMESPACE

class manager : public QWidget
{
    Q_OBJECT

public:
    manager(QWidget *parent = nullptr);
    ~manager();

public slots:
    void LoadPage(int pageIndex);
    void BtnLoadDataClick(QString str,int search_kind);
    void PageChange(int currentPage);


    //void text_from_interface(QString str);
private slots:
    void on_AddMany_clicked();
    void on_AddOnly_clicked();
    void on_Add_return_clicked();
    void reshow();


signals:
    void item_clicked(QString isbn_clicked, User user_now);
    void send_AddSignal();

private:
    Ui::manager *ui;
    PageWidget *pageWidget;
    PageT *pageT;
    Book_addOnly *fmain;

};
#endif // manager_H
