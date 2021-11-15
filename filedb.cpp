#include "filedb.h"

#include<string>
#include<fstream>
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;


FileDB::FileDB(string path)
{
    rootpath=path;
}



template<typename T>
int FileDB::select(string db_name,T &entity,vector<string>&value,vector<T>& result)
{
    ifstream readFile;

    try
    {
        T tem;
        int tsize=sizeof(tem);
        readFile.open(rootPath+db_name+".dat",ios::in|ios::out|ios::binary);
        if(!readFile)
        {
            ios_base::failure fail("error");
            throw fail;
        }
        if(value[0]=="all")
        {
            while(readFile.read(reinterpret_cast<char*>(&tem),tsize))
            {
                //去掉标记为已经删除的数据
                if(!tem.flag)
                    result.push_back(tem);
            }
        }
        else
        {
            if(value.size()==2)
            {
                if(value[1]=="id")
                {
                    selectId(readFile,entity.getId(),result);
                }
                else
                {
                    string type_name=tem.getElemType(value[1]);
                    if(type_name=="int")
                        selectInt(readFile,value[1],entity.getIntElemByName(value[1]),result);
                    else if(type_name=="float")
                        selectFloat(readFile,value[1],entity.getFloatElemByName(value[1]),result);
                    else
                        selectChars(readFile,value[1],entity.getCharElemByName(value[1]),result);
                }
            }
            else
            {
                selectMany(readFile,entity,value,result);
            }
        }
        readFile.close();
        return result.size();
    }
    catch(ios_base::failure &fail)
    {
        cout<<fail.what()<<endl;
        return -1;
    }
}

//筛选出对应db_name的表单 其中db_name中表单的对应实体为T 查询的字段为value，如果value为all，则全部选择，id则选择唯一的编号，其余则选择对应的list
/*下述的select都不用管，为select中封装的，其对应实现只有上方一个函数*/

/*
 * 假如查询所有则value[0]为all
 * 加入查询单项则value[0]置为非all，value[1]置为对应查询的属性例如isbn id等等
 * 多项查询则放在value[1] value[2] id和name等多个匹配
 * 下value含义相同
 */

template<typenam T>
void FileDB::selectInt(ifstream &readFile,string valueName,int value,vector<T>& result)
{
    T temp;
    int tsize=sizeof(T);
    while(readFile.read(reinterpret_cast<char*>(&temp),tsize))
    {
        if(!temp.flag&&temp_getIntElemByName(valueName)==value)
        {
            result.push_back(temp);
        }
    }
}

template<typenam T>
void FileDB::selectFloat(ifstream &readFile,string valueName,float value,vector<T>& result)
{
    T temp;
    int tsize=sizeof(T);
    while(readFile.read(reinterpret_cast<char*>(&temp),tsize))
    {
        if(!temp.flag&&temp_getFloatElemByName(valueName)==value)
        {
            result.push_back(temp);
        }
    }
}

template<typenam T>
void FileDB::selectChars(ifstream &readFile,string valueName,char* value,vector<T>& result)
{
    T temp;
    int tsize=sizeof(T);
    while(readFile.read(reinterpret_cast<char*>(&temp),tsize))
    {
        if(!temp.flag&&!strcmp(temp_getCharElemByName(valueName),value))
        {
            result.push_back(temp);
        }
    }
}


template<typename T>
void FileDB::selectId(ifstream &readFile,int id,vector<T>&result)
{
    T tem;
    readFile.seekg(id*sizeof(tem),ios::beg);
    readFile.read(reinterpret_cast<char*>(&tem),sizeof(tem));
    if(!tem.flag)
        result.push_back(tem);
}

//返回查找唯一id下的查询

template<typename T>
void FileDB::selectMuch(ifstream &readFile,T& entity,vector<string>&value,vector<T>&result)
{
    T tem;
    int tsize=sizeof(T);

    vector<string>ElemType;

    vector<int>IntValue;
    vector<float>floatValue;
    vector<char*>charValue;

    for(int i=1; i<value.size(); i++)
    {
        ElemType.push_back(entity.getElemType(value[i]));
        if(ElemType[i-1]=="int")
        {
            IntValue.push_back(entity.getIntElemByName(value[i]));
            floatValue.push_back(0);
            charValue.push_back("");
        }
        else if(ElemType[i-1]=="float")
        {
            floatValue.push_back(entity.getFloatElemByName(value[i]));
            IntValue.push_back(0);
            charValue.push_back("");
        }
        else
        {
            charValue.push_back(entity.getCharElemByName(value[i]));
            floatValue.push_back(0);
            IntValue.push_back("");
        }
    }

    while(readFile.read(reinterpret_cast<char*>(&tem),tsize))
    {
        if(!tem.flag)
        {
            int flag=0;

            for(int i=1; i<value.size(); i++)
            {
                if(ElemType[i-1]=="int")
                {
                    if(tem.getIntElemByName(value[i])!=IntValue[i-1])
                    {
                        flag=1;
                        break;
                    }
                }
                else if(ElemType[i-1]=="float")
                {
                    if(tem.getFloatElemByName(value[i])!=FloatValue[i-1])
                    {
                        flag=1;
                        break;
                    }
                }
                else
                {
                    if(strcmp(tem.getCharElemByName(value[i]),FloatValue[i-1]))
                    {
                        flag=1;
                        break;
                    }
                }
            }
            if(flag==0)
            {
                result.push_back(tem);
            }
        }
    }
}

template<typename T>
int FileDB::selectLike(string db_name,string value_name,char* value,vector<T>&result)
{
    ifstream readFile;
    try
    {
        T tem;
        int tsize=sizeof(tem);
        readFile.open(rootPath+db_name+".dat",ios::in|ios::out|ios::binary);
        if(!readFile)
        {
            ios_base::failure fail("ERROR");
            throw fail;
        }
        while(readFile.read(reinterpret_cast<char*>(&tem),tsize))
        {
            if(tem.flag!=-1&&strstr(tem.getCharElemByName(value_name),value))
            {
                result.push_back(tem);
            }
        }
        return result.size();
    }
    catch(ios_base::failure &fail)
    {
        cout<<fail.what()<<endl;
        return -1;
    }

}

//字符串的模糊查询

template<typename T>
int FileDB::insert(string db_name,vector<T>&entity)
{
    int id;
    ifstream readFile;
    ofstream writeFile;

    T tem;
    int tsize=sizeof(tem);

    try
    {
        readFile.open(rootPath+db_name+".dat",ios::in|ios::out|ios::binary);
        if (!readFile)
        {
            ios_base::failure fail("ERROR");
            throw fail;
        }

        readFile.seekg(1*sizeof(tem),ios::end);
        readFIle.read(reinterpret_cast<char*>(&tem),tsize);

        id=tem.getId();
        readFile.close();
        id++;

        writeFile.open(rootPath+db_name+".dat",ios::app|ios::binary);
        if(!writeFile)
        {
            ios_base::failure fail("ERROR");
            throw fail;
        }

        for(int i=0; i<entity.size(); i++)
        {
            entity[i].setId(id);
            entity[i].setflag(0);

            writeFile.write(reinterpret_cast<char*>&entity[i],sizeof(entity));//在思考这里是不是指针
            id++;
        }
        writeFile.close();
        return id;

    }
    catch (ios_base::failure &fail)
    {
        cout << fail.what() << endl;
        return -1;
    }

}
//增加db_name中的数据，entity为待增加的数据
//操作失败返回-1  成功返回某个正整数？预期设定为最后插入位置所属文件中的个数
//注明，因为每个表中唯一的数据不同，所以插入前应该手动先判断是否有重复数据

template<typename T>
int FileDB::Delete(string db_name,T& entity,vector<string>& value)
{
    ofstream writeFile;
    ifstream readFile;
    int res = 0;
    try
    {
        if (value[0] == "all")
        {
            writeFile.open(rootPath + db_name+ ".dat", ios::in | ios::out | ios::binary);
            if (!writeFile)
            {
                ios_base::failure fail("ERROR");
                throw fail;
            }
            writeFile.open(rootPath + db_name + ".dat", ios::trunc);
            writeFile.close();
            return 1;
        }

        writeFile.open(rootPath + db_name + ".dat", ios::in | ios::out | ios::binary);
        if (!writeFile)
        {
            ios_base::failure fail("ERROR");
            throw fail;
        }
        //id加速
        if (value[1] == "id")
        {
            T tem;
            tem.setflag(1);

            writeFile.seekp(entity.getId() * sizeof(tem), ios::beg);
            writeFile.write((char*)&tem, sizeof(tem));
            return 1;
        }

        //DELETE * FORM DB_NAME WHERE......
        readFile.open(rootPath + db_name + ".dat", ios::in | ios::out | ios::binary);
        if (!readFile)
        {
            ios_base::failure fail("ERROR");
            throw fail;
        }
        T tem;
        int tsize = sizeof(tem);

        //记忆化搜索
        vector<string>ElemType;

        vector<int>IntValue;
        vector<float>floatValue;
        vector<char*>charValue;

        for(int i=1; i<value.size(); i++)
        {
            ElemType.push_back(entity.getElemType(value[i]));
            if(ElemType[i-1]=="int")
            {
                IntValue.push_back(entity.getIntElemByName(value[i]));
                floatValue.push_back(0);
                charValue.push_back("");
            }
            else if(ElemType[i-1]=="float")
            {
                floatValue.push_back(entity.getFloatElemByName(value[i]));
                IntValue.push_back(0);
                charValue.push_back("");
            }
            else
            {
                charValue.push_back(entity.getCharElemByName(value[i]));
                floatValue.push_back(0);
                IntValue.push_back("");
            }
        }

        for (int count = 0; readFile.read(reinterpret_cast<char*>(&tem), tsize); count++)
        {
            //去除id为-1的无效数据
            if (!tem.flag)
            {
                int flag = 1;
                //遍历选择条件
                for (int i = 1; i < value.size(); i++)
                {
                    if (ElemType[i-1] == "int")
                    {
                        if (tem.getIntElemByName(value[i-1]) != IntValue[i-1])
                        {
                            flag = 0;
                            break;
                        }
                    }
                    else if (ElemType[i-1] == "float")
                    {
                        if (tem.getFloatElemByName(value[i]) != FloatValue[i])
                        {
                            flag = 0;
                            break;
                        }
                    }
                    else
                    {
                        if (strcmp(temp.getCharElemByName(value[i]), CharValue[i]))
                        {
                            flag = 0;
                            break;
                        }
                    }
                }
                //符合条件，删除
                if (flag)
                {
                    res++;
                    //移动文件指针，在count * sizeof(entity)出重写数据，将id置为-1
                    writeFile.seekp(count * sizeof(entity), ios::beg);
                    tem.setflag(1);
                    writeFile.write((char*)&tem, sizeof(tem));
                }
            }
        }
        readFile.close();
        writeFile.close();
        return res;
    }//捕获文件操作异常，返回-1
    catch (ios_base::failure &fail)
    {
        cout << fail.what() << endl;
        return -1;
    }//捕获字段赋值异常，返回-1
    catch (const char* e)
    {
        cout << "exception: " << e << endl;
        return -1;
    }
}
//这个尽量不要使用value[0]=all,会直接清空文件！！！
//删除db_name中的数据，其中entity代表删除的数据
//操作失败返回-1 成功返回最后一次影响的行数
//删除前应该先手动去数据库中查找每一条数据对应的数据库实体是否存在

template<typename T>
int FileDB::update(string db_name,T& select_entity,T& new_entity,vector<string>& value)
{
    ofstream writeFile;
    ifstream readFile;
    try
    {
        writeFile.open(rootPath + db_name + ".dat", ios::in | ios::out | ios::binary);
        if (!writeFile)
        {
            ios_base::failure fail("ERROR");
            throw fail;
        }
        //id加速
        if (value[1] == "id")
        {
            new_entity.setId(select.getId());
            new_entity.setDirty(0);
            writeFile.seekp(select_entity.getId() * sizeof(select_entity), ios::beg);
            writeFile.write((char*)&new_entity, sizeof(new_entity));
            return select.getId();
        }
        readFile.open(rootPath + db_name + ".dat", ios::in | ios::out | ios::binary);
        if (!readFile)
        {
            ios_base::failure fail("ERROR");
            throw fail;
        }
        T temp;


        T tem;
        int tsize = sizeof(tem);

        //记忆化搜索
        vector<string>ElemType;

        vector<int>IntValue;
        vector<float>floatValue;
        vector<char*>charValue;

        for(int i=1; i<value.size(); i++)
        {
            ElemType.push_back(select_entity.getElemType(value[i]));
            if(ElemType[i-1]=="int")
            {
                IntValue.push_back(select_entity.getIntElemByName(value[i]));
                floatValue.push_back(0);
                charValue.push_back("");
            }
            else if(ElemType[i-1]=="float")
            {
                floatValue.push_back(select_entity.getFloatElemByName(value[i]));
                IntValue.push_back(0);
                charValue.push_back("");
            }
            else
            {
                charValue.push_back(select_entity.getCharElemByName(value[i]));
                floatValue.push_back(0);
                IntValue.push_back("");
            }
        }

        for (int count = 0; readFile.read(reinterpret_cast<char*>(&tem), tsize); count++)
        {
            //去除id为-1的无效数据
            if (!tem.flag)
            {
                int flag = 1;
                //遍历选择条件
                for (int i = 1; i < value.size(); i++)
                {
                    if (ElemType[i-1] == "int")
                    {
                        if (tem.getIntElemByName(value[i-1]) != IntValue[i-1])
                        {
                            flag = 0;
                            break;
                        }
                    }
                    else if (ElemType[i-1] == "float")
                    {
                        if (tem.getFloatElemByName(value[i]) != FloatValue[i])
                        {
                            flag = 0;
                            break;
                        }
                    }
                    else
                    {
                        if (strcmp(temp.getCharElemByName(value[i]), CharValue[i]))
                        {
                            flag = 0;
                            break;
                        }
                    }
                }
                if (flag)
                {
                    new_entity.setId(tem.id);
                    new_entity.setflag(0);
                    writeFile.seekp(count * sizeof(select_entity), ios::beg);
                    writeFile.write((char*)&new_entity, sizeof(new_entity));
                }
            }
        }
        readFile.close();
        writeFile.close();
        return 1;
    }//捕获文件操作异常，返回-1
    catch (ios_base::failure &fail)
    {
        cout << fail.what() << endl;
        return -1;
    }//捕获字段赋值异常，返回-1
    catch (const char* e)
    {
        cout << "exception: " << e << endl;
        return -1;
    }
}
//在db_name中根据select 将对应数据更新为new_entity,其中value为选择字段
//操作失败返回-1 成功返回受影响的行数
