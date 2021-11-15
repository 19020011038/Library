#ifndef PARTITION_H
#define PARTITION_H
#include"all_file_classes.h"
#include <QMainWindow>
#include "PageTable.h"
#include "PageWidget.h"
#include <QListWidget>
#include "loadpage.h"
#include <config.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Partition; }
QT_END_NAMESPACE

class Partition : public QMainWindow
{
    Q_OBJECT

public:
    Partition(QWidget *parent = nullptr);
    ~Partition();
    void setID(char *id)
    {
        strcpy(ID,id);
    }

public slots:
    void Show_Partitionpage();
    void listwidget_clicked_to_main(QListWidgetItem * item);
    void on_pushButton_return_clicked();
    void get_info(char *id);


signals:
    void Loadage_signal();

    void listwidget_clicked(int id, User user_from_main);
    void sendsignal();

private slots:
    //void on_btnskip_clicked();



private:
    Ui::Partition *ui;

    LoadPage * load_page;
    char ID[ACCOUNT_SIZE];
};
#endif // PARTITION_H
