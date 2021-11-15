#include "formuser.h"
#include "ui_formuser.h"

FormUser::FormUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormUser)
{
    ui->setupUi(this);
}

FormUser::~FormUser()
{
    delete ui;
}
