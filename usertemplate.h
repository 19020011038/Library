#ifndef USERTEMPLATE_H
#define USERTEMPLATE_H

#include <QDialog>
#include <config.h>
#include<person.h>
#include"book_rank.h"
#include"partition.h"
#include"searchandselect.h"
#include <book_ditails.h>
#include"manager_interface.h"



namespace Ui {
class usertemplate;
}

class usertemplate : public QDialog
{
    Q_OBJECT

public:
    explicit usertemplate(QWidget *parent = nullptr);
    ~usertemplate();
    void setID(char *id)
    {
        cout << "get parameter" << id<<endl;
        for (int i = 0 ; i < ACCOUNT_SIZE; i ++)
            this->ID[i] = id[i];
        cout << "in set id "<< ID<<endl;
    }
    char *getID(){return ID;}

private slots:
    void on_pushButton_4_clicked();
    void reshow();
    void get_student_info(char *id);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

signals:
    void sendsignal(char *id);

private:
    Ui::usertemplate *ui;
    char ID[ACCOUNT_SIZE];
    Person *fmain;
    Book_Rank *book_rank;
    //Partition *partition;
    SearchAndSelect *search;
    Partition *pt;
    LoadPage *lp;
    Book_Ditails *bookditail;
    Manager_Interface *manager_interface;
};

#endif // USERTEMPLATE_H
