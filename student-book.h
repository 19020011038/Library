#ifndef STUDENTBOOK_H
#define STUDENTBOOK_H

#include"config.h"
#include <iostream>

using namespace std;

class StudentBook{
private:
    char isbn[ISBN_SIZE];
    char account[ACCOUNT_SIZE];
    int mark;
    int recommend;
    int isAppointed;
    int isInBorrowedHistory;
    int id;
    int flag;

public:

    void setId(int id){this->id=id;}
    int getId(){return this->id;}
    void setflag(int flag){this->flag=flag;}
    int getflag(){return flag;}
    char* getIsbn(){return this->isbn;}
    void setIsbn(const char* isbn){
        for (int i = 0; i < ISBN_SIZE; i ++)
            this->isbn[i] = isbn[i];
    }
    char* getAccount(){return account;}
    void setAccount(const char* account){
        for (int i = 0; i < ACCOUNT_SIZE; i ++)
            this->account[i] = account[i];
    }
    int getRecommend(){return this->recommend;}
    void setRecommend(int recommend){this->recommend = recommend;}
    int getMark(){return this->mark;}
    void setMark(int mark){this->mark = mark;}
    int getIsAppointed(){return this->isAppointed;}
    void setIsAppointed(int isAppointed){this->isAppointed = isAppointed;}
    int getIsInBorrowedHistory(){return this->isInBorrowedHistory;}
    void setIsInBorrowedHistory(int isInBorrowedHistory){this->isInBorrowedHistory = isInBorrowedHistory;}

    string getElemType(string Elem) {
        if (Elem == "id") return typeid(id).name();
        else if (Elem == "flag") return typeid(flag).name();
        else if (Elem == "isbn") return typeid(isbn).name();
        else if (Elem == "account") return typeid(account).name();
        else if (Elem == "mark") return typeid(mark).name();
        else if (Elem == "recommend")return typeid(recommend).name();
        else if (Elem == "isAppointed")return typeid(isAppointed).name();
        else if (Elem == "isInBorrowedHistory")return typeid(isInBorrowedHistory).name();
        else {
            throw "Field  Not Found!";
        }
    }
    int getIntElemByName(string Elem) {
        if (Elem == "id") return id;
        else if (Elem == "flag") return flag;
        else if (Elem == "mark")return mark;
        else if (Elem == "recommend")return recommend;
        else if (Elem == "isAppointed")return isAppointed;
        else if (Elem == "isInBorrowedHistory")return isInBorrowedHistory;
        else {
            throw "Field  Not Found!";
        }
    }
    float getFloatElemByName(string Elem) {
        return 1;
    }
    char* getCharElemByName(string Elem) {
        if (Elem == "isbn") return  isbn;
        else if (Elem == "account") return this->account;
        else {
            throw "Field  Not Found!";
        }
    }
};

#endif // STUDENTBOOK_H
