#ifndef MODIFY_BOOK_H
#define MODIFY_BOOK_H

#include <QMainWindow>
#include <iostream>
#include <config.h>

using namespace std;


namespace Ui {
class modify_book;
}

class modify_book : public QMainWindow
{
    Q_OBJECT

public:
    explicit modify_book(QWidget *parent = 0);
    ~modify_book();

    void set_isbn(char *id)
    {
        strcpy(book_ISBN,id);
    }
    void get_book_info(char *id);//将原来的图书信息显示到对应位置上去

private slots:
    void on_pushButton_return_clicked();
    void on_submit_clicked();

    void on_pushButton_1_clicked();
signals:
    void send_returnSignal();
    void show_signal(char *id);

private:
    Ui::modify_book *ui;
    char book_ISBN[ISBN_SIZE];
};

#endif // MODIFY_BOOK_H
