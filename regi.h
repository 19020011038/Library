#ifndef REGI_H
#define REGI_H

#include <QDialog>
#include"mainwindow.h"

namespace Ui {
class regi;
}

class regi : public QDialog
{
    Q_OBJECT

public:
    explicit regi(QWidget *parent = nullptr);
    ~regi();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

private:
    Ui::regi *ui;
};

#endif // REGI_H
