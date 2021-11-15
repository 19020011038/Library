#ifndef PREBORROW_H
#define PREBORROW_H

#include <QMainWindow>
#include <config.h>

namespace Ui {
class preborrow;
}

class preborrow : public QMainWindow
{
    Q_OBJECT

public:
    explicit preborrow(QWidget *parent = 0);
    ~preborrow();
    void setID(char *id);

private slots:
    //void reshow();//重新

    void on_pushButton_return_clicked();
    void get_preborrow(char* student_id);//通过当前学生id，获取其预约的书籍列表

    void delete_preborrow();//根据图书的ISBN取消预约
    void get_bookdetail(char *ISBN);



signals:
    void send_preborrow_return_signal();


private:
    Ui::preborrow *ui;
    char ID[ACCOUNT_SIZE];
};

#endif // PREBORROW_H
