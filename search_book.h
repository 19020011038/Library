#ifndef SEARCH_BOOK_H
#define SEARCH_BOOK_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class search_book;
}

class search_book : public QWidget
{
    Q_OBJECT

public:
    explicit search_book(QWidget *parent = nullptr);
    ~search_book();

signals:
    void search_btn_clicked(QString str, int search_kind);

    //void text_to_interface(QString str);

public slots:
//    void slot_text_edited(QString str);
//    void slot_btn_clicked();
    void slot_search();
//    QString slot_select();

private:
    Ui::search_book *ui;
};

#endif // SEARCH_BOOK_H
