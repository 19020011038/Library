#ifndef PERSON_H
#define PERSON_H

#include <QMainWindow>
#include<borrowing.h>
#include<collection.h>
#include<setting.h>
#include<preborrow.h>
#include "user.h"


namespace Ui {
class Person;
}

class Person : public QMainWindow
{
    Q_OBJECT

public:
    explicit Person(QWidget *parent = 0);
    ~Person();

    char *get_ID()
    {
        return ID;
    }
    void setID(char *id)
    {
        strcpy(ID,id);
    }


private slots:
    void on_pushButton_close_clicked();
    void on_borrow_clicked();
    void on_preborrow_clicked();
    void on_setting_clicked();
    void on_have_clicked();
    void reshow();
    void get_student_info(char *student_id);


signals:
    void sendSignal();
    void sendID(char *id);
    void sendID_2(char *id);
    void sendID_3(char *id);
    void sendID_4(char *id);


private:
    Ui::Person *ui;
    borrowing *borrow;
    Collection *collection;
    setting *set;
    preborrow *preb;

    char ID[ACCOUNT_SIZE];
};

#endif // PERSON_H
