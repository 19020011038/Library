#ifndef ADD_BOOK_H
#define ADD_BOOK_H

#include <QMainWindow>
#include <config.h>

namespace Ui {
class Add_Book;
}

class Add_Book : public QMainWindow
{
    Q_OBJECT

public:
    explicit Add_Book(QWidget *parent = 0);
    ~Add_Book();
    void setIsbn(char *ISBN);

private slots:
    void on_pushButton_return_2_clicked();
    void on_submit_2_clicked();


signals:
    void send_returnSiganl();


private:
    Ui::Add_Book *ui;
    char id[ACCOUNT_SIZE];
};

#endif // ADD_BOOK_H
