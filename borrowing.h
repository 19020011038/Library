#ifndef BORROWING_H
#define BORROWING_H

#include <QMainWindow>
#include <config.h>
//#include<QTableView>

namespace Ui {
class borrowing;
}

class borrowing : public QMainWindow
{
    Q_OBJECT

public:
    explicit borrowing(QWidget *parent = 0);
    ~borrowing();
    void set_ID(char *id);


private slots:
    void return_book();
    void on_pushButton_return_clicked();

    void get_bookdetail(char* ISBN);
    void get_borrowbook(char* student_id);//得到当前学生的借阅书籍的信息



signals:
    void sendreturnSignal();

private:
    Ui::borrowing *ui;

    char ID[ACCOUNT_SIZE];
};

#endif // BORROWING_H
