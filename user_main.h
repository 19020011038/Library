#ifndef USER_MAIN_H
#define USER_MAIN_H

#include <QMainWindow>
#include "PageWidget.h"
#include "user.h"
#include "user_page.h"
#include "user_addonly.h"

namespace Ui {
class user_main;
}

class user_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit user_main(QWidget *parent = nullptr);
    ~user_main();

public slots:
    void LoadPage(int pageIndex);
    void BtnLoadDataClick(QString str,int search_kind);
    void PageChange(int currentPage);

    //void items_clicked(QString str);

    //void text_from_interface(QString str);

private slots:
    void on_pushButton_return_clicked();
    void on_AddOnly_clicked();
    void on_AddMany_clicked();
    void reshow();

signals:
    //void item_clicked(QString isbn_clicked, User user_now);
    void send_return2Signal();


private:
    Ui::user_main *ui;
    PageWidget *pageWidget;
    user_page * userp;
    user_addonly *fmain;
};

#endif // USER_MAIN_H
