#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include "config.h"

using namespace std;


class Book
{
private:
    char isbn[ISBN_SIZE];
    int id_total;
    char name[BOOK_NAME_SIZE];
    char author[AUTHOR_SIZE];
    char image[IMAGE_SIZE];
    char publisher[PUBLISHER_SIZE];
    char publish_date[PUBLISH_DATE_SIZE];
    float price;
    int left;
    int storage;
    int num_mark;
    int num_borrow;
    char description[DESCRIPTION_SIZE];
    char classification[CLASSIFICATION_SIZE];
    char available_appointment_time[TIME_SIZE];
    int id;
    int flag;

public:

    int getId(){return id;}
    void setId(int id){this->id=id;}
    int getflag(){return flag;}
    void setflag(int flag){this->flag=flag;}
    char* getIsbn(){return this->isbn;}
    void setIsbn(const char* isbn){
        for (int i = 0; i < ISBN_SIZE; i ++)
            this->isbn[i] = isbn[i];
    }
    int getIdTotal(){return this->id_total;}
    void setIdTotal(int id_total){this->id_total = id_total;}
    char* getName(){return this->name;}
    void setName(const char* name){
        for (int i = 0; i < BOOK_NAME_SIZE; i ++ )
            this->name[i] = name[i];
    }
    char* getAuthor(){return this->author;}
    void setAuthor(const char* author){
        for (int i = 0; i < AUTHOR_SIZE; i ++ )
            this->author[i] = author[i];
    }
    char* getImage(){return this->image;}
    void setImage(const char* image){
        for (int i = 0; i < IMAGE_SIZE; i ++ )
            this->image[i] = image[i];
    }
    char* getPublisher(){return this->publisher;}
    void setPublisher(const char* publisher){
        for (int i = 0; i < PUBLISHER_SIZE; i ++ )
            this->publisher[i] = publisher[i];
    }
    char* getPublishDate(){return this->publish_date;}
    void setPublishDate(const char* publish_date){
        for (int i = 0; i < PUBLISH_DATE_SIZE; i ++ )
            this->publish_date[i] = publish_date[i];
    }
    float getPrice(){return this->price;}
    void setPrice(float price){this->price = price;}
    int getLeft(){return this->left;}
    void setLeft(int left){this->left = left;}
    int getStorage(){return this->storage;}
    void setStorage(int storage){this->storage = storage;}
    int getNumMark(){return this->num_mark;}
    void setNumMark(int num_mark){this->num_mark = num_mark;}
    int getNumBorrow(){return this->num_borrow;}
    void setNumBorrow(int num_borrow){this->num_borrow = num_borrow;}
    char* getDescription(){return this->description;}
    void setDescription(const char* description){
        for (int i = 0; i < DESCRIPTION_SIZE; i ++ )
            this->description[i] = description[i];
    }
    char* getClassifition(){return this->classification;}
    void setClassification(const char* classification){
        for (int i = 0; i < CLASSIFICATION_SIZE; i ++ )
            this->classification[i] = classification[i];
    }
    char* getAvailableAppointmentTime(){return this->available_appointment_time;}
    void setAvailableAppointmentTime(const char* available_appointment_time){
        for (int i = 0; i < TIME_SIZE; i ++)
            this->available_appointment_time[i] = available_appointment_time[i];
    }


    string getElemType(string Elem) {
        if (Elem == "isbn") return typeid(isbn).name();
        else if (Elem == "id_total") return typeid(id_total).name();
        else if (Elem == "name") return typeid(name).name();
        else if (Elem == "author") return typeid(author).name();
        else if (Elem == "image") return typeid(image).name();
        else if(Elem == "publisher")return typeid(publisher).name();
        else if(Elem == "publish_date")return typeid(publish_date).name();
        else if(Elem == "price")return typeid(price).name();
        else if(Elem == "left")return typeid(left).name();
        else if(Elem == "storage")return typeid(storage).name();
        else if(Elem == "num_mark")return typeid(num_mark).name();
        else if(Elem == "num_borrow")return typeid(num_borrow).name();
        else if(Elem=="description")return typeid(description).name();
        else if(Elem == "classification")return typeid(classification).name();
        else if(Elem=="id")return typeid(id).name();
        else if(Elem=="flag")return typeid(flag).name();
        else if (Elem == "available_appointment_time")return typeid(available_appointment_time).name();
        else {
            throw "Field  Not Found!";
        }
    }
    int getIntElemByName(string Elem) {
        if (Elem == "id") return id;
        else if (Elem == "flag") return flag;
        else if(Elem=="id_total")return id_total;
        else if(Elem=="left")return left;
        else if(Elem=="storage")return storage;
        else if(Elem=="num_mark")return num_mark;
        else if(Elem=="num_borrow")return num_borrow;
        else {
            throw "Field  Not Found!";
        }
    }
    float getFloatElemByName(string Elem) {
        if(Elem == "price")return price;
        else {
            throw "Field  Not Found!";
        }
    }
    char* getCharElemByName(string Elem) {
        if (Elem == "isbn") return  isbn;
        else if (Elem == "name") return name;
        else if (Elem == "author") return author;
        else if (Elem == "image") return image;
        else if (Elem == "publisher") return publisher;
        else if (Elem == "publish_date") return publish_date;
        else if (Elem == "description")return description;
        else if (Elem == "classification")return classification;
        else if (Elem == "available_appointment_time") return this->available_appointment_time;
        else {
            throw "Field  Not Found!";
        }
    }

};
#endif // BOOK_H
