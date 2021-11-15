#include "modify_book.h"
#include "ui_modify_book.h"
#include "book.h"
#include "tool.h"
#include <QMessageBox>

modify_book::modify_book(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::modify_book)
{
    ui->setupUi(this);

    connect(this,SIGNAL(show_signal(id)),this,SLOT(get_book_info(id)));

    //this->get_book_info();
}

modify_book::~modify_book()
{
    delete ui;
}


void modify_book::on_pushButton_return_clicked()
{
    emit send_returnSignal();
    this->close();
}

void modify_book::on_submit_clicked()
{
    Utils mutils = Utils();

    Book book;

    Book book_old =mutils.GetBook(book_ISBN);


    int flag=0;

//    QString str = ui->ISBN->text();
//    QByteArray ba = str.toLocal8Bit();

//    QString str2 = ui->ISBN->text();
//    QByteArray ba2 = str2.toLocal8Bit();
//    char *isbn = ba2.data();
//    if(str2.length()<=0||str2.length()>=ISBN_SIZE)flag=1;

//    book.setIsbn(isbn);

    QString str = ui->ISBN->text();

    QByteArray ba = str.toLocal8Bit();

    QString str2 = ui->ISBN->text();
    QByteArray ba2 = str2.toLocal8Bit();
    char *isbn = ba2.data();
    const char* check_result1 = mutils.CheckBookIsbn(isbn);

    book.setIsbn(isbn);


//    str = ui->name->text();
//    ba = str.toLocal8Bit();
//    char *name = ba.data();
//    if(str.length()<=0||str.length()>=BOOK_NAME_SIZE)flag=1;

//    book.setName(name);
    str = ui->name->text();
    ba = str.toLocal8Bit();
    char *name = ba.data();
    const char* check_result2 = mutils.CheckBookName(name);
    if (mutils.compair_const("OK", check_result2)){
        book.setName(name);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result2);
            msgBox.exec();
        }
    }

//    str = ui->author->text();
//    ba = str.toLocal8Bit();
//    char *author = ba.data();
//    if(str.length()<=0||str.length()>=AUTHOR_SIZE)flag=1;
//    book.setAuthor(author);
    str = ui->author->text();
    ba = str.toLocal8Bit();
    char *author = ba.data();
    const char* check_result3 = mutils.CheckBookAuthor(author);
    if (mutils.compair_const("OK", check_result3)){
        book.setAuthor(author);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result3);
            msgBox.exec();
        }
    }

//    str = ui->image->text();
//    ba = str.toLocal8Bit();
//    char *image = ba.data();
//    if(str.length()<=0||str.length()>=IMAGE_SIZE)flag=1;
//    book.setImage(image);
    str = ui->image->text();
    ba = str.toLocal8Bit();
    char *image = ba.data();
    const char* check_result4 = mutils.CheckBookImage(image);
    if (mutils.compair_const("OK", check_result4)){
        book.setImage(image);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result4);
            msgBox.exec();
        }

    }

//    str = ui->publish->text();
//    ba = str.toLocal8Bit();
//    char *publish = ba.data();
//    if(str.length()<=0||str.length()>=PUBLISHER_SIZE)flag=1;
//    book.setPublisher(publish);
    str = ui->publish->text();
    ba = str.toLocal8Bit();
    char *publish = ba.data();
    const char* check_result5 = mutils.CheckBookPublisher(publish);
    if (mutils.compair_const("OK", check_result5)){
        book.setPublisher(publish);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result5);
            msgBox.exec();
        }

    }

//    str = ui->publish_date_label->text();
//    ba = str.toLocal8Bit();
//    char *publish_date = ba.data();
//    if(str.length()<=0||str.length()>=PUBLISH_DATE_SIZE)flag=1;
//    book.setPublishDate(publish_date);
    str = ui->publish_date_label->text();

    ba = str.toLocal8Bit();
    char *publish_date = ba.data();
    const char* check_result6 = mutils.CheckBookPublishDate(publish_date);
    if (mutils.compair_const("OK", check_result6)){
        book.setPublishDate(publish_date);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result6);
            msgBox.exec();
        }

    }


//    str = ui->price->text();
//    float price = str.toFloat();
//    if(price<=0)flag=1;
//    book.setPrice(price);



    str = ui->price->text();
    ba = str.toLocal8Bit();
    char *price_str = ba.data();
    if (strlen(price_str) > 8){
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText("价格过大");
            msgBox.exec();
        }
    }
    int count_point = 0;
    for (int i = 0; i < strlen(price_str); i ++)
    {
        if(flag == 1) break;
        //先判合法字符
        if (!(price_str[i]>='0'&&price_str[i]<='9') && price_str[i] != '.')
        {

            flag = 1;
            QMessageBox msgBox;
            msgBox.setText("请输入正确的价格");
            msgBox.exec();
            break;

        }else{
            //全部为合法字符了


            if (price_str[i]=='.')
            {
                //小数点前必须有数字
                if(i == 0){
                    flag = 1;
                    QMessageBox msgBox;
                    msgBox.setText("请输入正确的价格");
                    msgBox.exec();
                    break;
                }

                //判断只能有一个小数点
                count_point ++;
                if (count_point == 2){
                    flag = 1;
                    QMessageBox msgBox;
                    msgBox.setText("请输入正确的价格");
                    msgBox.exec();
                    break;
                }

            }
        }
    }


    if (!flag){
        float price = str.toFloat();
        const char* check_result7 = mutils.CheckBookPrice(price);
        if (mutils.compair_const("OK", check_result7)){
            book.setPrice(price);
        }else{
            if(!flag){
                flag = 1;
                QMessageBox msgBox;
                msgBox.setText(check_result7);
                msgBox.exec();
            }

        }


        cout<<book.getPrice()<<"    price"<<endl;

    }




    if (!flag)
    {
            book.setIdTotal(book_old.getIdTotal());
            book.setLeft(book_old.getLeft());
            book.setStorage(book_old.getStorage());
            book.setNumBorrow(book_old.getNumBorrow());
            book.setNumMark(book_old.getNumMark());
    }


    int cla[30]={0};
    cla[0]=ui->cla_0->isChecked();
    cla[1]=ui->cla_1->isChecked();
    cla[2]=ui->cla_2->isChecked();
    cla[3]=ui->cla_3->isChecked();
    cla[4]=ui->cla_4->isChecked();
    cla[5]=ui->cla_5->isChecked();
    cla[6]=ui->cla_6->isChecked();
    cla[7]=ui->cla_7->isChecked();
    cla[8]=ui->cla_8->isChecked();
    cla[9]=ui->cla_9->isChecked();
    cla[10]=ui->cla_10->isChecked();
    cla[11]=ui->cla_11->isChecked();
    cla[12]=ui->cla_12->isChecked();
    cla[13]=ui->cla_13->isChecked();
    cla[14]=ui->cla_14->isChecked();
    cla[15]=ui->cla_16->isChecked();
    cla[16]=ui->cla_17->isChecked();
    cla[17]=ui->cla_18->isChecked();
    cla[18]=ui->cla_19->isChecked();
    cla[19]=ui->cla_20->isChecked();
    cla[20]=ui->cla_21->isChecked();
    cla[21]=ui->cla_22->isChecked();

    QString clas;


    map<int,QString>mp;
    mp.insert({0,"哲学"});
    mp.insert({1,"人文社科综合"});
    mp.insert({2,"管理学"});
    mp.insert({3,"政治"});
    mp.insert({4,"法律"});
    mp.insert({5,"经济"});
    mp.insert({6,"文化/教育"});
    mp.insert({7,"语言/文学"});
    mp.insert({8,"艺术"});
    mp.insert({9,"历史"});
    mp.insert({10,"数学"});
    mp.insert({11,"物理"});
    mp.insert({12,"化学/材料"});
    mp.insert({13,"理工综合"});
    mp.insert({14,"地球科学"});
    mp.insert({15,"生物"});
    mp.insert({16,"医学/药学"});
    mp.insert({17,"农业/水产",});
    mp.insert({18,"工业技术"});
    mp.insert({19,"计算机/网络"});
    mp.insert({20,"环境"});
    mp.insert({21,"其他"});

    int clas_num = 0;
    for(int i=0;i<=21;i++)
    {
        if(cla[i]==1)
        {
            clas_num++;
            clas+=mp[i];
            clas+=" ";
        }
    }

    if (clas_num == 0){
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText("请选择分区");
            msgBox.exec();
        }

    }

    if (clas_num > 3){
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText("至多选择三个分区");
            msgBox.exec();
        }

    }

    if (!flag){

        ba = clas.toLocal8Bit();
        char *Classification = ba.data();
        if(clas.length()<=0||clas.length()>=CLASSIFICATION_SIZE)flag=1;

        book.setClassification(Classification);
    }

//    str = ui->description->toPlainText();
//    ba = str.toLocal8Bit();
//    if(str.length()==0||str.length()>=DESCRIPTION_SIZE)flag=1;
//    char *description =ba.data();
//    book.setDescription(description);
    str = ui->description->toPlainText();
    ba = str.toLocal8Bit();
//    if(str.length()==0||str.length()>=DESCRIPTION_SIZE)flag=1;

    char *description =ba.data();
    const char* check_result8 = mutils.CheckBookDescription(description);
    if (mutils.compair_const("OK", check_result8)){
            book.setDescription(description);
    }else{
        if (!flag){
            flag = 1;
            QMessageBox msgBox;
            msgBox.setText(check_result8);
            msgBox.exec();
        }

    }

    if(flag == 1)
    {
        QMessageBox msgBox;
        msgBox.setText("输入出现错误");
        msgBox.exec();
    }
    else
    {
        if(mutils.UpdateBook(book_old,book)==1)
        {
            vector<int>old_id;
            for(int i=0;i<=21;i++)
            {
                BookClassification bc = BookClassification();
                bc.setIsbn(isbn);
                bc.setClassification(i);
                if(mutils.CheckBookClassificationExist(bc)==1)
                {
                    mutils.DeleteBookClassification(bc);
                }
                else continue;
            }

            for(int i=0;i<=21;i++)
            {
                if(cla[i]==1)
                {
                    BookClassification bc = BookClassification();
                    bc.setIsbn(isbn);
                    bc.setClassification(i);
                    mutils.InsertBookClassification(bc);
                }
            }
            QMessageBox msgBox;
            msgBox.setText("提交成功");
            msgBox.exec();
            on_pushButton_return_clicked();

        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("更新失败");
            msgBox.exec();
            on_pushButton_return_clicked();
        }
    }

}

void modify_book::on_pushButton_1_clicked()
{
    const char* c ="12306";
    int len = strlen(c);
    char *b = new char[len];
    strcpy(b, c);

    Utils mutils = Utils();

    Book book= Book();
    book.setIsbn(b);
    if(mutils.CheckBookExist(book))cout<<"find it"<<endl;

    this->get_book_info(b);
    //emit show_signal(b);

}

void modify_book::get_book_info(char *id)
{
    set_isbn(id);
    Utils mutils = Utils();


    Book book = mutils.GetBook(book_ISBN);
    cout<<"book";

    char *ch;
    ch = book.getIsbn();

    QString Isbn =QString::fromLocal8Bit(ch);
    ui->ISBN->setText(Isbn);

    ch = book.getName();
    QString name = QString::fromLocal8Bit(ch);
    ui->name->setText(name);

    ch = book.getAuthor();
    QString author = QString::fromLocal8Bit(ch);
    ui->author->setText(author);

    ch = book.getImage();
    QString Image = QString::fromLocal8Bit(ch);
    ui->image->setText(Image);

    ch = book.getPublisher();
    QString publisher = QString::fromLocal8Bit(ch);
    ui->publish->setText(publisher);

    ch = book.getPublishDate();
    QString publish_date = QString::fromLocal8Bit(ch);
    ui->publish_date->setText(publish_date);

    float price = book.getPrice();
    QString Price = QString("%1").arg(price);
    ui->price->setText(Price);

    int num = book.getStorage();
    cout<<num<<endl;
    QString Num= QString("%2").arg(num);
    ui->num_2->setText(Num);


    ch = book.getDescription();
    QString description = QString::fromLocal8Bit(ch);
    ui->description->setPlainText(description);

}
/*
 *
 *删除函数放在这里，根据ISBN删除该类图书，并弹出对应的提示框
void test::delete_book(string ISBN)
{

}

*/
