#ifndef BOOK_INFORMATION_H
#define BOOK_INFORMATION_H

#include <QWidget>

namespace Ui {
class Book_Information;
}

class Book_Information : public QWidget
{
    Q_OBJECT

public:
    explicit Book_Information(QWidget *parent = nullptr);
    ~Book_Information();

    void set_book_name(QString str);
    void set_book_author(QString str);
    void set_book_publisher(QString str);
    void set_book_publish_time(QString str);
    void set_book_borrownumber(QString str);
    void set_book_price(QString str);
    void set_book_marknumber(QString str);
    void set_book_storagenumber(QString str);
    void set_book_leftnumber(QString str);
    void set_book_discription(QString str);
    void set_book_photo(QString str);

public slots:
    void mark_clicked();
    void appoint_clicked();

signals:
    void btn_mark_clicked();
    void btn_appoint_clicked();

private:
    Ui::Book_Information *ui;
};

#endif // BOOK_INFORMATION_H
