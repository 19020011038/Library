#ifndef SEARCHANDSELECT_H
#define SEARCHANDSELECT_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class SearchAndSelect;
}

class SearchAndSelect : public QWidget
{
    Q_OBJECT

public:
    explicit SearchAndSelect(QWidget *parent = nullptr);
    ~SearchAndSelect();

signals:
    void search_btn_clicked(QString str, int search_kind);

    //void text_to_interface(QString str);

public slots:
//    void slot_text_edited(QString str);
//    void slot_btn_clicked();
    void slot_search();
//    QString slot_select();

private:
    Ui::SearchAndSelect *ui;

//    QLineEdit *m_pLineEdit;
//    QPushButton *m_pBtn;
//    enum EBtnStatus{ESEARCH, ECLOSE};
//    EBtnStatus m_iCurBtnStatus;
};

#endif // SEARCHANDSELECT_H
