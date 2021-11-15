#ifndef USER_H
#define USER_H
#include<typeinfo>
#include<iostream>
#include"config.h"
using namespace std;

class User
{
private:
    int id;
    int flag;
    int isAdmin;
    char account[ACCOUNT_SIZE];
    char password[PASSWORD_SIZE];
    char name[USER_NAME_SIZE];
    int sex;
    char major[MAJOR_SIZE];
    int num_borrowed;
    int num_appointed;
    int frooze;
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
    int getIsAdmin()
    {
        return isAdmin;
    }
    void setIsAdmin(int isAdmin)
    {
        this->isAdmin = isAdmin;
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
    char* getPassword()
    {
        return this->password;
    }
    void setPassword(const char* password)
    {
        for (int i = 0; i < PASSWORD_SIZE; i ++ )
            this->password[i] = password[i];
    }
    char* getName()
    {
        return this->name;
    }
    void setName(const char* name)
    {
        for (int i = 0; i < USER_NAME_SIZE; i ++ )
            this->name[i] = name[i];
    }
    int getSex()
    {
        return this->sex;
    }
    void setSex(int sex)
    {
        this->sex = sex;
    }
    char* getMajor()
    {
        return this->major;
    }
    void setMajor(const char* major)
    {
        for (int i = 0; i < MAJOR_SIZE; i ++ )
            this->major[i] = major[i];
    }
    int getNumBorrowed(){return num_borrowed;}
    void setNumBorrowed(int num_borrowed){this->num_borrowed = num_borrowed;}
    int getNumAppointed(){return num_appointed;}
    void setNumAppointed(int num_appointed){this->num_appointed = num_appointed;}
    void setFrooze(int frooze){this->frooze=frooze;}
    int getFrooze(){return frooze;}


    string getElemType(string Elem)
    {
        if (Elem == "id")
            return typeid(id).name();
        else if (Elem == "flag")
            return typeid(flag).name();
        else if(Elem == "isAdmin")return typeid(isAdmin).name();
        else if (Elem == "account")
            return typeid(account).name();
        else if (Elem == "password")
            return typeid(password).name();
        else if (Elem == "name")
            return typeid(name).name();
        else if(Elem == "sex")
            return typeid(sex).name();
        else if(Elem == "major")
            return typeid(major).name();
        else if(Elem == "num_borrowed")
            return typeid(num_borrowed).name();
        else if(Elem == "num_appointed")
            return typeid(num_appointed).name();
        else if(Elem == "frooze")return typeid(frooze).name();
        else
        {
            throw "Field  Not Found!";
        }
    }
    int getIntElemByName(string Elem)
    {
        if (Elem == "id")
            return id;
        else if (Elem == "flag")
            return flag;
        else if (Elem == "isAdmin")return isAdmin;
        else if (Elem == "sex")return sex;
        else if (Elem == "frooze")return frooze;
        else if (Elem == "num_borrowed")return num_borrowed;
        else if (Elem == "num_appointed")return num_appointed;
        else
        {
            throw "Field  Not Found!";
        }
    }
    float getFloatElemByName(string Elem)
    {
        return 0;
    }
    char* getCharElemByName(string Elem)
    {
        if (Elem == "account")
            return  account;
        else if (Elem == "password")
            return password;
        else if (Elem == "name")
            return name;
        else if(Elem=="major")
            return major;
        else
        {
            throw "Field  Not Found!";
        }
    }
};

#endif // USER_H
