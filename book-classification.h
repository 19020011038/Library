#ifndef BOOKCLASSIFICATION_H
#define BOOKCLASSIFICATION_H
#include<iostream>
#include"config.h"

using namespace std;

class BookClassification{
private:
    int classification;
    char isbn[ISBN_SIZE];
    int id;
    int flag;
public:
    void setId(int id){this->id=id;}
    int getId(){return id;}
    void setflag(int flag){this->flag=flag;}
    int getflag(){return flag;}
    int getClassification(){return this->classification;}
    void setClassification(int classification){this->classification = classification;}
    char* getIsbn(){return this->isbn;}
    void setIsbn(const char* isbn){
        for (int i = 0; i < ISBN_SIZE; i ++)
            this->isbn[i] = isbn[i];
    }
    string getElemType(string Elem) {
        if (Elem == "id") return typeid(id).name();
        else if (Elem == "flag") return typeid(flag).name();
        else if (Elem == "isbn") return typeid(isbn).name();
        else if (Elem == "classification") return typeid(classification).name();
        else {
            throw "Field  Not Found!";
        }
    }
    int getIntElemByName(string Elem) {
        if (Elem == "id") return id;
        else if (Elem == "flag") return flag;
        else if(Elem == "classification")return classification;
        else {
            throw "Field  Not Found!";
        }
    }
    float getFloatElemByName(string Elem) {
        return 1;
    }
    char* getCharElemByName(string Elem) {
        if (Elem == "isbn") return  this->isbn;
        else {
            throw "Field  Not Found!";
        }
    }
};

#endif // BOOKCLASSIFICATION_H
