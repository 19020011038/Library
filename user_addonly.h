#ifndef USER_ADDONLY_H
#define USER_ADDONLY_H

#include <QMainWindow>

namespace Ui {
class user_addonly;
}

class user_addonly : public QMainWindow
{
    Q_OBJECT

public:
    explicit user_addonly(QWidget *parent = 0);
    ~user_addonly();

private slots:
    void on_pushButton_return_clicked();
    void on_submit_clicked();//提交信息，并对信息进行检查

signals:
    void send_returnSignal();

private:
    Ui::user_addonly *ui;
};

#endif // USER_ADDONLY_H
