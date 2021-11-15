#ifndef LOADPAGE_H
#define LOADPAGE_H

#include <QWidget>
#include <QListWidgetItem>
#include "PageTable.h"
#include "PageWidget.h"
#include "user.h"

namespace Ui {
class LoadPage;
}

class LoadPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoadPage(QWidget *parent = nullptr);
    ~LoadPage();

//自定义槽函数
public slots:
    void BtnLoadDataClick();
    void PageChange(int currentPage);

    void Show_Loadpage(int id, User user_from_partition);

signals:
    void Partitionpage();
    void quit();
    void ISBN_to_main_SIGNAL(QString str, User user_loadpage);

private slots:
    void on_pushButton_2_clicked();
    void ISBN_to_main_slot(QString str);

private:
    Ui::LoadPage *ui;
    PageWidget *pageWidget;
    PageTable *pageTable;

    void LoadPagee(int pageIndex);
};

#endif // LOADPAGE_H
