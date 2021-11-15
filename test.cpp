#include "test.h"
#include "ui_test.h"

test::test(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::test)
{
    ui->setupUi(this);
}

test::~test()
{
    delete ui;
}
