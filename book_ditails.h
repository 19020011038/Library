#ifndef BOOK_DITAILS_H
#define BOOK_DITAILS_H

#include <QWidget>
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Book_Ditails; }
QT_END_NAMESPACE

class Book_Ditails : public QWidget
{
    Q_OBJECT

public:
    Book_Ditails(QWidget *parent = nullptr);
    ~Book_Ditails();
    void LoadPage();

public slots:
    void show_bookditals(QString isbn_clicked, User user_now);

    void appoint_book_detail();
    void mark_book_detail();
    void judge_borrow(int row, int col);

private:
    Ui::Book_Ditails *ui;
};
#endif // BOOK_DITAILS_H
