#ifndef SETTING_H
#define SETTING_H

#include <QMainWindow>
#include<change_information.h>
#include <config.h>

namespace Ui {
class setting;
}

class setting : public QMainWindow
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = 0);
    ~setting();
    void setID(char *id);
    char *getID()
    {
        return ID;
    }


private slots:
    void on_exit_clicked(char* student_id);//将该学号的学生登出，先弹出一个提示框更加合理
    void on_pushButton_return_clicked();
    void get_info(char *id);
    void reshow();
    void on_change_information_clicked();



    void on_exit_clicked();

signals:
    void send_exitsignal();
    void send_set_return_signal();
    void send_ID(char *id);

private:
    Ui::setting *ui;
    change_information *change_UI;
    char ID[ACCOUNT_SIZE];
};

#endif // SETTING_H
