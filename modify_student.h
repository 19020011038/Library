#ifndef MODIFY_STUDENT_H
#define MODIFY_STUDENT_H

#include <QMainWindow>
#include <config.h>

namespace Ui {
class modify_student;
}

class modify_student : public QMainWindow
{
    Q_OBJECT

public:
    explicit modify_student(QWidget *parent = 0);
    ~modify_student();
   // void get_student_info();//根据学号得到用户原本信息
    void set_id(char *id)
    {
        strcpy(student_id,id);
    }
    void get_student_info(char *id);//根据学号得到用户原本信息

private slots:
    void on_submit_clicked();//提交用户修改信息
    void on_pushButton_return_clicked();
    void on_pushButton_1_clicked();


signals:
    void send_returnSignal();

private:
    Ui::modify_student *ui;
    char student_id[ACCOUNT_SIZE];
};

#endif // MODIFY_STUDENT_H
