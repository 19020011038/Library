#ifndef ISBNSTUDENT_H
#define ISBNSTUDENT_H
#include<iostream>
//#include"config.h"
using namespace std;

class IsbnStudent{
private:
    int id;
    char isbn[ISBN_SIZE];
    char account[ACCOUNT_SIZE];
    int flag;
public:
    int getId(){return this->id;}
    void setId(int id){this->id=id;}
    char* getIsbn(){return this->isbn;}
    void setIsbn(char* isbn){
        for (int i = 0; i < ISBN_SIZE; i ++)
            this->isbn[i] = isbn[i];
    }
    char* getAccount()
    {
        return this->account;
    }
    void setAccount(const char* account)
    {
        for (int i = 0; i < ACCOUNT_SIZE; i ++)
            this->account[i] = account[i];
    }
    void setflag(int flag)
    {
        this->flag=flag;
    }
    int getflag()
    {
        return this->flag;
    }


    string getElemType(string Elem) {
        if (Elem == "id") return typeid(id).name();
        else if (Elem == "flag") return typeid(flag).name();
        else if (Elem == "isbn") return typeid(isbn).name();
        else if (Elem == "account") return typeid(account).name();
        else {
            throw "Field  Not Found!";
        }
    }
    int getIntElemByName(string Elem) {
        if (Elem == "id") return id;
        else if (Elem == "flag") return flag;
        else {
            throw "Field  Not Found!";
        }
    }
    float getFloatElemByName(string Elem) {
        return 1;
    }
    char* getCharElemByName(string Elem) {
        if (Elem == "isbn") return  isbn;
        else if (Elem == "account") return account;
        else {
            throw "Field  Not Found!";
        }
    }
};

#endif // ISBNSTUDENT_H
