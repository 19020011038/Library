#ifndef BOOK_ADDONLY_H
#define BOOK_ADDONLY_H

#include <QMainWindow>

namespace Ui {
class Book_addOnly;
}

class Book_addOnly : public QMainWindow
{
    Q_OBJECT

public:
    explicit Book_addOnly(QWidget *parent = 0);
    ~Book_addOnly();
private slots:
    void on_pushButton_return_clicked();
    void on_submit_clicked();

signals:
    void send_returnSignal();

private:
    Ui::Book_addOnly *ui;
};

#endif // BOOK_ADDONLY_H
