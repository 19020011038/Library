#ifndef RANK_H
#define RANK_H
#include<iostream>
#include"config.h"
using namespace std;
class Rank{
private:
    int id;
    char isbn[ISBN_SIZE];
    int flag;
public:
    int getId()
    {
        return id;
    }
    void setId(int id)
    {
        this->id=id;
    }
    void setflag(int flag)
    {
        this->flag=flag;
    }
    int getflag()
    {
        return flag;
    }
    char* getIsbn(){return this->isbn;}
    void setIsbn(const char* isbn){
        for (int i = 0; i < ISBN_SIZE; i ++)
            this->isbn[i] = isbn[i];
    }

    string getElemType(string Elem) {
        if (Elem == "id") return typeid(id).name();
        else if (Elem == "flag") return typeid(flag).name();
        else if (Elem == "isbn") return typeid(isbn).name();
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
        else {
            throw "Field  Not Found!";
        }
    }
};

#endif // RANK_H
