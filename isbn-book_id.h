#ifndef ISBNBOOK_ID_H
#define ISBNBOOK_ID_H

#include<iostream>
#include"config.h"

using namespace std;


class IsbnBookId{
private:
    char isbn[ISBN_SIZE];
    int book_id;
    char borrow_account[ACCOUNT_SIZE];
    int isBorrowed;
    char time_borrow[TIME_SIZE];
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
    int getBookId(){return this->book_id;}
    void setBookId(int book_id){this->book_id = book_id;}
    char* getBorrowAccount(){return this->borrow_account;}
    void setBorrowAccount(const char* borrow_account){
        for (int i = 0; i < ACCOUNT_SIZE; i ++)
            this->borrow_account[i] = borrow_account[i];
    }
    int getIsBorrowed(){return this->isBorrowed;}
    void setIsBorrowed(int isBorrowed){this->isBorrowed = isBorrowed;}
    char* getTimeBorrow(){return this->time_borrow;}
    void setTimeBorrow(const char* time_borrow){
        for (int i = 0; i < TIME_SIZE; i ++)
            this->time_borrow[i] = time_borrow[i];
    }

    string getElemType(string Elem) {
        if (Elem == "id") return typeid(id).name();
        else if (Elem == "flag") return typeid(flag).name();
        else if (Elem == "isbn") return typeid(isbn).name();
        else if (Elem == "book_id") return typeid(book_id).name();
        else if (Elem == "borrow_account") return typeid(borrow_account).name();
        else if (Elem == "isBorrowed")return typeid(isBorrowed).name();
        else if (Elem == "time_borrow")return typeid(time_borrow).name();
        else {
            throw "Field  Not Found!";
        }
    }
    int getIntElemByName(string Elem) {
        if (Elem == "id") return id;
        else if (Elem == "flag") return flag;
        else if (Elem == "book_id")return book_id;
        else if (Elem == "isBorrowed")return isBorrowed;
        else {
            throw "Field  Not Found!";
        }
    }
    float getFloatElemByName(string Elem) {
        return 1;
    }
    char* getCharElemByName(string Elem) {
        if (Elem == "isbn") return  isbn;
        else if (Elem == "borrow_account") return this->borrow_account;
        else if (Elem == "time_borrow") return this->time_borrow;
        else {
            throw "Field  Not Found!";
        }
    }
};

#endif // ISBNBOOK_ID_H
