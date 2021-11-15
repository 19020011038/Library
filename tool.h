#ifndef TOOL_H
#define TOOL_H
#include <iostream>
#include"all_file_classes.h"
#include<vector>
#include <string.h>
#include <QString>

using namespace std;

class Utils{
public:

    /*使用举例：
     * #include"tool.h"
     * Utils mUtils = Utils();
     * if(mUtils.UpdateMarkRank())
     *     printf("success");
     *
     *
     * 说明：默认参数均合法
     * 比如：GetUser函数默认参数中的user是存在的，因此若要使用该函数，请先调用CheckUserExist()进行检查
     *
     *
    */


    //*******************************
    // 以下均是对文件的单个唯一条目进行的操作
    bool CheckUserExist(User user); //参数：学生对象，返回是否存在该条目


    bool CheckBookExist(Book book); //参数：图书对象，返回是否存在该条目


    bool CheckIsbnBookIdExist(IsbnBookId ibi); //参数：IsbnBookId对象，返回是否存在该条目


    bool CheckStudentBookExist(StudentBook sb); //参数：StudentBook对象，返回是否存在该条目


    bool CheckBookClassificationExist(BookClassification bc); //参数：BookClassification对象，返回是否存在该条目


    bool InsertUser(User user); //参数：User对象，进行插入操作，返回是操作是否成功


    bool InsertBook(Book book); //参数：Book对象，进行插入操作，返回是操作是否成功


    bool InsertIsbnBookId(IsbnBookId ibi); //参数：IsbnBookId对象，进行插入操作，返回是操作是否成功


    bool InsertStudentBook(StudentBook sb); //参数：StudentBook对象，进行插入操作，返回是操作是否成功


    bool InsertBookClassification(BookClassification bc); //参数：BookClassification对象，进行插入操作，返回是操作是否成功


    bool DeleteUser(User user); //参数：User对象，进行删除操作，返回操作是否成功的结果


    bool DeleteBook(Book book); //参数：Book对象，进行删除操作，返回操作是否成功的结果


    bool DeleteIsbnBookId(IsbnBookId ibi); //参数：IsbnBookId对象，进行删除操作，返回操作是否成功的结果


    bool DeleteStudentBook(StudentBook sb); //参数：StudentBook对象，进行删除操作，返回操作是否成功的结果


    bool DeleteBookClassification(BookClassification bc); //参数：BookClassification对象，进行删除操作，返回操作是否成功的结果


    User GetUser(char* account); //参数为用户账号，返回该账号对应的学生对象，账号不存在则返回一个默认构建的User对象


    Book GetBook(char* isbn); //参数为图书isbn，返回该账号对应的图书对象，isbn不存在则返回一个默认构建的Book对象


    IsbnBookId GetIsbnBookId(char* isbn, int book_id); //参数为图书isbn，返回该账号对应的图书对象，isbn不存在则返回一个默认构建的User


    StudentBook GetStudentBook(char* account, char* isbn);
    //参数1为学生账号，参数2为图书isbn，返回唯一的StudentBook对象，检索对象不存在则返回一个默认构建的StudentBook对象


    BookClassification GetBookClassification(char* isbn, int classification_id);
    //参数1为图书isbn，参数2为分区id，返回唯一的BookClassification对象，检索对象不存在则返回一个默认构建的BookC对象


    bool UpdateUser(User before, User after); //参数1为需要修改的User对象，参数2为修改后的User对象，返回修改操作是否成功的结果


    bool UpdateBook(Book before, Book after); //参数1为需要修改的Book对象，参数2为修改后的Book对象，返回修改操作是否成功的结果


    bool UpdateIsbnBookId(IsbnBookId before, IsbnBookId after); //参数1为需要修改的IsbnBookId对象，参数2为修改后的IsbnBookId对象，返回修改操作是否成功的结果



    bool UpdateStudentBook(StudentBook before, StudentBook after);
    //参数1为需要修改的StudentBook对象，参数2为修改后的StudentBook对象，返回修改操作是否成功的结果


    bool UpdateBookClassification(BookClassification before, BookClassification after);
    //参数1为需要修改的BookClassification对象，参数2为修改后的BookClassification对象，返回修改操作是否成功的结果
    //以上均是对单个文件的操作*******************************



    bool AddBook(Book book);//暂不需要用此函数。。。。参数为新增图书，函数使用条件：已判断书库中无此书，返回操作成功结果


    bool RemoveBook(Book book);//参数为删除图书，使用条件：书库中有此书，返回操作是否成功结果（失败的原因可能是有人在借书）


    bool RemoveUser(User user);//删除用户，参数为用户对象，返回操作是否成功的结果（失败可能是由于用户有未还图书）


    int Register(User user); //参数：学生对象，功能：注册新学生。返回值：0:账号已存在，1:注册成功, -1注册失败


    int Login(char* account, char* password); //参数1:账号，参数2:密码，功能：用户登录。返回值：0:账户不存在；1:登陆成功；2:密码错误


    bool GetMarkRank(vector<Book>&result); //参数为存结果列表，返回图书列表对象，内容为按收藏数排序的前十个图书


    bool GetBorrowRank(vector<Book>&result); //参数为存结果列表，返回图书列表对象，内容为按历史借阅总数排序的前十个图书


    bool UpdateMarkRank(); //更新收藏排行榜，返回操作是否成功的结果


    bool UpdateBorrowRank(); //更新历史借阅榜排行榜，返回操作是否成功的结果


    bool GetBooksByBookName(char* name, vector<Book>&result); //参数1为图书名，参数2为存结果列表，操作为根据书名检索图书，返回操作是否成功的结果


    bool GetBooksByAuthor(char* author, vector<Book>&result); //参数1为作者名，参数2为存结果列表，操作为根据作者名检索图书，返回操作是否成功的结果


    Book GetBookByIsbn(char* isbn); //参数1为isbn，返回isbn对应图书对象


    bool GetBooksByClassificationId(int classification_id, vector<Book>&result); //参数1为分区id，参数2为存结果列表，操作为根据分区id检索图书，返回操作是否成功的结果


    bool GetRecommendList(User user, vector<Book>&result); //参数1为User对象,参数2为存结果列表，返回值为该用户的推荐书目列表


    bool UpdateRecommandList(User user); //参数为用户对象，操作为更新对该用户的推荐图书


    bool GetMarkList(User user, vector<Book>&result); //参数1为User对象，参数2为存结果列表，返回该用户的收藏列表


    bool GetBorrowingList(User user, vector<IsbnBookId>&result); //参数1为User对象，参数2为存结果列表，返回该用户的正在借书列表


    bool GetAppointmentList(User user, vector<Book>&result); //参数1为User对象，参数2为存结果列表，返回该用户预约的图书列表


    bool CheckIfBookAppointed(Book book); //参数为图书对象，返回该书是否被预约


    User GetAppointmentUser(Book book); //参数为图书对象，返回对该类书的预约的唯一用户，默认该书已被预约


    bool CheckIfBookIdBorrowed(Book book, int book_id); //参数1为图书对象,参数2为单本id，返回该书是否被借阅


    User GetBorrowUser(Book book, int book_id); //参数1为图书对象，参数2为单本Id,返回借阅这本书的用户


    bool Borrow(User user, Book book, int book_id); //参数1:借书者用户，参数2:所借图书唯一编号，参数3:借书id，返回操作是否成功
    //借阅条件：需先判断该book_id单书是否被借出,若剩余量为0，需判断该用户是否是预约用户。默认已满足借阅条件


    bool Return(User user, Book book, int book_id); //参数1:还书者用户，参数2:所还图书唯一编号，参数3:还书id，返回操作是否成功


    bool Appoint(User user, Book book); //参数1:预约者用户，参数2:所预约图书isbn,返回操作是否成功，需检查是否符合预约条件：剩余量为0且无人预约


    bool PreAppoint(User user, Book book); //参数1:取消预约者用户，参数2:所取消预约图书isbn,返回操作是否成功


    bool GetBookIdsOfBook(Book book, vector<IsbnBookId>&result); //参数1为Book对象， 参数2为存结果列表，即该isbn所对应isbn-book_id文件中所有条目，返回操作是否成功的结果


    bool SetMark(User user, Book book, int isMark); //参数1:收藏者用户，参数2:所收藏图书isbn，参数3:加入收藏1取消收藏0， 返回操作是否成功


    bool GetBooksOfClassification(int classification_id, vector<Book>&result); //参数1为分区ID,参数2为存结果列表，返回操作是否成功


    bool GetClassificationsOfBook(Book book, vector<int>&result); //参数为1为图书isbn，参数2为所属分区id存储列表，返回操作是否成功的结果


    bool CheckAdmin(User user); //参数为User对象，返回该用户是否是管理员，是true，不是false


    bool CheckIsFrooze(User user); //参数为用户对象，返回该用户是否被冻结的结果


    bool SetUserFrooze(User user, int frooze); //参数1为用户对象，参数2为设置用户的冻结状态，1冻结2不冻结，返回操作是否成功的结果


    int TransformClassification(QString str); //参数为分区的名称，返回分区编号.无对应分区返回-1

    const char* char_to_const(char* a){
        const char* b = a;
        return b;
    }

    char* const_to_char(const char* a){
        int len = strlen(a);
        char *b = new char[len];
        strcpy(b, a);
        return b;
    }

    bool compair_const(const char* a, const char* b){
        if (strlen(a) != strlen(b))
            return false;
        else{
            bool flag = true;
            for (int i = 0; i < strlen(a); i ++ )
                if (a[i] != b[i]){
                    flag = false;
                    break;
                }
            return flag;
        }
    }

    const char* CheckUserAccount(char* account){

        if(strlen(account) == 0) return "请输入账户";

        if (strlen(account) != 11) return "账户长度必须为11个字符";

        User user = User();
        user.setAccount(char_to_const(account));

        if(CheckUserExist(user)) return "账户已存在";

        for (int i = 0; i < strlen(account); i ++){
            if (!(account[i] <= '9' && account[i] >= '0')){
                return "账户只能为0-9数字";
            }
        }

        return "OK";

    }

    const char* CheckUserPassword(char* password){

        if(strlen(password) == 0) return "请输入密码";

        if (strlen(password) > 16) return "密码长度不得大于16字符";

        if(strlen(password) < 8) return "密码长度不得小于8字符";

        for (int i = 0; i < strlen(password); i ++){
            char c = password[i];
            if (!(c<='z'&&c>='a') && !(c<='Z'&&c>='A') && !(c>='0'&&c<='9')){
                return "密码只能为大小写字母和0-9数字";
            }
        }

        return "OK";

    }

    const char* CheckUserName(char* name){

        if (strlen(name) == 0) return "请输入姓名";

        if (strlen(name) > 15) return "姓名不得长于15个字符";

        return "OK";
    }

    const char* CheckUserMajor(char* major){

        if (strlen(major) == 0) return "请输入专业";

        if (strlen(major) > 30) return "专业不得长于30个字符";

        return "OK";
    }

    const char* CheckBookIsbn(char* isbn){

        if (strlen(isbn) == 0) return "请输入isbn";

        if (strlen(isbn) != 13) return "isbn不为13位";

        for (int i = 0; i < strlen(isbn); i ++){
            if (!(isbn[i] <= '9' && isbn[i] >= '0')){
                return "isbn只能为0-9数字";
            }
        }

        Book book = Book();
        book.setIsbn(char_to_const(isbn));

        if (CheckBookExist(book)) return "图书已存在";

        return "OK";
    }

    const char* CheckBookName(char* name){
        if (strlen(name) == 0) return "请输入书名";
        if (strlen(name) > 30) return "书名不得超过30字符";
        return "OK";
    }

    const char* CheckBookAuthor(char* author){
        if (strlen(author) == 0) return "请输入作者名";
        if (strlen(author) > 30) return "作者名不得超过30字符";
        return "OK";
    }

    const char* CheckBookImage(char* image){
        if (strlen(image) == 0) return "请输入图片路径";
        if (strlen(image) > 100) return "图片路径不得超过100字符";
        return "OK";
    }

    const char* CheckBookPublisher(char* publisher){
        if (strlen(publisher) == 0) return "请输入出版社";
        if (strlen(publisher) > 30) return "出版社不得超过30字符";
        return "OK";
    }

    const char* CheckBookPublishDate(char* publish_date){
        if (strlen(publish_date) == 0) return "请输入出版时间";
        if (strlen(publish_date) > 20) return "出版时间不得超过20字符";
        return "OK";
    }

    const char* CheckBookDescription(char* description){
        if (strlen(description) == 0) return "请输入简介";
        if (strlen(description) > 300) return "简介不得超过300字符";
        return "OK";
    }

    const char* CheckBookClassification(char* classification){
        if (strlen(classification) == 0) return "请输入图书分类";
        if (strlen(classification) > 100) return "图书分类不得超过100字符";
        return "OK";
    }

    const char* CheckBookPrice(float price){
        if (price < 0) return "价格不能为负数";
        return "OK";
    }

    const char* CheckBookNum(int num){
        if (num <= 0) return "数量必须为正数";
        return "OK";
    }

    bool GetUserByName(char* name, vector<User>&result);//需要先判定是否有此User

    bool GetUserByMajor(char* major, vector<User>&result);//需要先判定是否有此User
};

#endif // TOOL_H
