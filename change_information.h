#ifndef CHANGE_INFORMATION_H
#define CHANGE_INFORMATION_H

#include <QMainWindow>
#include <config.h>

namespace Ui {
class change_information;
}

class change_information : public QMainWindow
{
    Q_OBJECT

public:
    explicit change_information(QWidget *parent = 0);
    ~change_information();
private slots:
    //void change_password();//修改密码，根据前端输入数据来判断和当前学生的原密码是否一致
    void on_pushButton_return_clicked();
    void on_pushButton_change_password_clicked();
    void setID(char* id);
signals:
    void return_setting();
    
private:
    Ui::change_information *ui;
    char ID[ACCOUNT_SIZE];
};

#endif // CHANGE_INFORMATION_H
