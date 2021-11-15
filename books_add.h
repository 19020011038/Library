#ifndef BOOKS_ADD_H
#define BOOKS_ADD_H

#include <QMainWindow>
#include "book_addonly.h"
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;


namespace Ui {
class Books_add;
}

class Books_add : public QMainWindow
{
    Q_OBJECT

public:
    explicit Books_add(QWidget *parent = 0);
    ~Books_add();

private slots:
    void on_AddMany_clicked();
    void on_AddOnly_clicked();
    void on_Add_return_clicked();
    void reshow();
    void on_delete_book_clicked(char *isbn);

signals:
    void send_AddSignal();

private:
    Ui::Books_add *ui;
    Book_addOnly *fmain;
};

#endif // BOOKS_ADD_H
