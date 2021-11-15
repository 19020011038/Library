#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"usertemplate.h"
#include"regi.h"
#include"person.h"
#include "admin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_login_clicked();

    void on_pushButton_2_clicked();


private:
    Ui::MainWindow *ui;
    usertemplate *fmain;
    Admin *admin;
    char student_id[ACCOUNT_SIZE];
signals:
    void sendsignal(char *student_id);
};
#endif // MAINWINDOW_H
