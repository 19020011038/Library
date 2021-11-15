#ifndef MANAGER_INTERFACE_H
#define MANAGER_INTERFACE_H

#include <QWidget>
#include "PageTable.h"
#include "PageWidget.h"
#include "book.h"
#include <vector>
#include "user.h"
#include <config.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Manager_Interface; }
QT_END_NAMESPACE

class Manager_Interface : public QWidget
{
    Q_OBJECT

public:
    Manager_Interface(QWidget *parent = nullptr);
    ~Manager_Interface();
    void setID(char *id)
    {
        strcpy(ID,id);
    }

public slots:
    void LoadPage(int pageIndex, vector<Book> bk);
    void BtnLoadDataClick(QString str,int search_kind);
    void PageChange(int currentPage);

    void items_clicked(QString str);
    void get_student_info(char *id);
    //void text_from_interface(QString str);
    void on_pushButton_return_clicked();

signals:
    void item_clicked(QString isbn_clicked, User user_now);
    void sendSignal();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Manager_Interface *ui;
    PageWidget *pageWidget;
    PageTable *pageTable;
    char ID[ACCOUNT_SIZE];

};
#endif // MANAGER_INTERFACE_H
