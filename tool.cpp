#include<iostream>
#include"config.h"
#include"tool.h"
#include"filedb.h"
#include<vector>
#include<string.h>
#include"rank.h"
#include"all_file_classes.h"
#include<QDateTime>
#include<map>
using namespace std;

FileDB db = FileDB("C://Users/yyx/Desktop/Library/db/");


//      int insert(string db_name,vector<T>&entity);
//      int Delete(string db_name,T& entity,vector<string>& value);
//      int update(string db_name,T& select_entity,T& new_entity,vector<string>& value);
//      int select(string db_name,T &entity,vector<string>&value,vector<T>&result);


bool Utils::CheckUserExist(User user) //参数：账户，返回是否存在该账户
{
    vector<string> value;
    value.push_back("not-all");
    value.push_back("account");
    vector<User> result;
    if (db.select("user", user, value, result) == -1)
        return false;
    return true;
}

bool Utils::CheckBookExist(Book book) //参数：isbn，返回是否存在该种书
{
    //cout"W";
    vector<string> value;
    value.push_back("not-all");
    value.push_back("isbn");
    vector<Book> result;
    if (db.select("book", book, value, result) == -1)
        return false;
    //coutresult.size()<<endl;
    return true;
}

bool Utils::CheckIsbnBookIdExist(IsbnBookId ibi){
    vector<string> vec;
    vec.push_back("not-all");
    vec.push_back("isbn");
    vec.push_back("book_id");
    vector<IsbnBookId> res;
    if (db.select("isbn-book_id", ibi, vec, res) != -1)
        return true;
    else
        return false;
}

bool Utils::CheckStudentBookExist(StudentBook sb){
    vector<string> vec;
    vec.push_back("not-all");
    vec.push_back("account");
    vec.push_back("isbn");
    vector<StudentBook> res;
    //cout"ISBN"<<sb.getIsbn()<<endl;
    //cout"account"<<sb.getAccount()<<endl;
    if (db.select("student-book", sb, vec, res) != -1)
        return true;
    else
        return false;
}

bool Utils::CheckBookClassificationExist(BookClassification bc){
    vector<string> vec;
    vec.push_back("not-all");
    vec.push_back("classification");
    vec.push_back("isbn");
    vector<BookClassification> res;
    if (db.select("book-classification", bc, vec, res) != -1)
        return true;
    else
        return false;
}

bool Utils::InsertUser(User user){
    if (!CheckUserExist(user)){
        vector<User> vec;
        vec.push_back(user);
        if (db.insert("user", vec) != -1)
            return true;
        else
            return false;
    }else{
        return false;
    }
}

bool Utils::InsertBook(Book book)  //参数为图书对象，功能为将图书插入数据文件，返回操作是否成功的结果
{
    if (!CheckBookExist(book)){
        vector<Book> entity;
        entity.push_back(book);
        if (db.insert("book", entity) != -1){
            return true;
        }else {
            return false;
        }
    }else {
        return false;
    }
}

bool Utils::InsertIsbnBookId(IsbnBookId ibi){
    if (!CheckIsbnBookIdExist(ibi)){
        vector<IsbnBookId> vec;
        vec.push_back(ibi);
        if (db.insert("isbn-book_id", vec) != -1)
            return true;
        else
            return false;
    }else {
        return false;
    }
}

bool Utils::InsertStudentBook(StudentBook sb){
    if (!CheckStudentBookExist(sb)){
        vector<StudentBook> vec;
        vec.push_back(sb);
        if (db.insert("student-book", vec) != -1)
            return true;
        else
            return false;
    }else {
        return false;
    }
}

bool Utils::InsertBookClassification(BookClassification bc){
    if (!CheckBookClassificationExist(bc)){
        vector<BookClassification> vec;
        vec.push_back(bc);
        if (db.insert("book-classification", vec) != -1)
            return true;
        else
            return false;
    }else {
        return false;
    }
}

bool Utils::DeleteUser(User user){
    if (CheckUserExist(user)){
        vector<string> vec;
        vec.push_back("not-all");
        vec.push_back("account");
        if (db.Delete("user", user, vec) != -1)
            return true;
        else
            return false;
    }else {
        return false;
    }
}

bool Utils::DeleteBook(Book book){
    if (CheckBookExist(book)){
        vector<string> vec;
        vec.push_back("not-all");
        vec.push_back("isbn");
        if (db.Delete("book", book, vec) != -1)
            return true;
        else
            return false;
    }else {
        return false;
    }
}

bool Utils::DeleteIsbnBookId(IsbnBookId ibi){
    if (CheckIsbnBookIdExist(ibi)){
        vector<string> vec;
        vec.push_back("isbn");
        vec.push_back("book_id");
        if (db.Delete("isbn-book_id", ibi, vec) != -1)
            return true;
        else
            return false;
    }else {
        return false;
    }
}

bool Utils::DeleteStudentBook(StudentBook sb){
    if (CheckStudentBookExist(sb)){
        vector<string> vec;
        vec.push_back("account");
        vec.push_back("isbn");
        if (db.Delete("student-book", sb, vec) != -1)
            return true;
        else
            return false;
    }else {
        return false;
    }
}

bool Utils::DeleteBookClassification(BookClassification bc){
    if (CheckBookClassificationExist(bc)){
        vector<string> vec;
        vec.push_back("classification");
        vec.push_back("isbn");
        if (db.Delete("book-classification", bc, vec) != -1)
            return true;
        else
            return false;
    }else {
        return false;
    }
}

User Utils::GetUser(char* account) //参数为学生账号，返回包含该学生信息的学生对象
{
    User user = User();
    user.setAccount(account);
    if (CheckUserExist(user))
    {
        vector<string> value;
        value.push_back("not-all");
        value.push_back("account");
        vector<User> result;
        int pos = db.select("user", user, value, result);
        return result.at(0);
    }
    else{
        User user2 = User();
        return user2;
    }
}

Book Utils::GetBook(char* isbn) // 参数为图书isbn，返回包含该图书信息的图书对象
{
    Book book = Book();
    book.setIsbn(isbn);
    if (CheckBookExist(book))
    {
        vector<string> value;
        value.push_back("not-all");
        value.push_back("isbn");
        vector<Book> result;
        int pos = db.select("book", book, value, result);
        return result.at(0);
    }
    else{
        Book book = Book();
        return book;
    }
}

IsbnBookId Utils::GetIsbnBookId(char* isbn, int book_id){
    IsbnBookId ibi = IsbnBookId();
    ibi.setIsbn(isbn);
    ibi.setBookId(book_id);
    if (CheckIsbnBookIdExist(ibi))
    {
        vector<string> value;
        value.push_back("not-all");
        value.push_back("isbn");
        value.push_back("book_id");
        vector<IsbnBookId> result;
        int pos = db.select("isbn-book_id", ibi, value, result);
        return result.at(0);
    }
    else{
        IsbnBookId ibi = IsbnBookId();
        return ibi;
    }
}

StudentBook Utils::GetStudentBook(char* account, char* isbn){
    StudentBook sb = StudentBook();
    sb.setIsbn(isbn);
    sb.setAccount(account);
    if (CheckStudentBookExist(sb))
    {
        vector<string> value;
        value.push_back("not-all");
        value.push_back("isbn");
        value.push_back("account");
        vector<StudentBook> result;
        int pos = db.select("student-book", sb, value, result);
        return result.at(0);
    }
    else{
        StudentBook sb = StudentBook();
        return sb;
    }
}

BookClassification Utils::GetBookClassification(char* isbn, int classification_id){
    BookClassification bc = BookClassification();
    bc.setIsbn(isbn);
    bc.setClassification(classification_id);
    if (CheckBookClassificationExist(bc))
    {
        vector<string> value;
        value.push_back("not-all");
        value.push_back("isbn");
        value.push_back("classification");
        vector<BookClassification> result;
        int pos = db.select("book-classification", bc, value, result);
        return result.at(0);
    }
    else{
        BookClassification bc = BookClassification();
        return bc;
    }
}

bool Utils::UpdateUser(User before, User after){
    if (CheckUserExist(before)){
        vector<string> vec;
        vec.push_back("not-all");
        vec.push_back("account");
        if (db.update("user", before, after, vec) != -1)
            return true;
        else
            return false;
    }else{
        return false;
    }
}

bool Utils::UpdateBook(Book before, Book after){
    //cout"mmmmmmmmmmmmmm";
    if (CheckBookExist(before)){
        vector<string> vec;
        vec.push_back("not-all");
        vec.push_back("isbn");
        if (db.update("book", before, after, vec) != -1)
            return true;
        else
            return false;
    }else{
        return false;
    }


}

bool Utils::UpdateIsbnBookId(IsbnBookId before, IsbnBookId after){
    if (CheckIsbnBookIdExist(before)){
        vector<string> vec;
        vec.push_back("not-all");
        vec.push_back("isbn");
        vec.push_back("book_id");
        Book book = Book();
        book.setIsbn(before.getIsbn());
        vector<IsbnBookId> vec01;
        if(GetBookIdsOfBook(book, vec01)){
            cout <<"........................pos01 in update                          "<<vec01.size()<<endl;
        }
        if (db.update("isbn-book_id", before, after, vec) != -1){
            vector<IsbnBookId> vec02;
            if(GetBookIdsOfBook(book, vec02)){
                cout<< "........................pos02 in update                      "<<vec02.size()<<endl;
            }
            return true;
        }
        else
            return false;
    }else{
        return false;
    }
}

bool Utils::UpdateStudentBook(StudentBook before, StudentBook after){
    if (CheckStudentBookExist(before)){
        vector<string> vec;
        vec.push_back("not-all");
        vec.push_back("account");
        vec.push_back("isbn");
        if (db.update("student-book", before, after, vec) != -1)
            return true;
        else
            return false;
    }else{
        return false;
    }
}

bool Utils::UpdateBookClassification(BookClassification before, BookClassification after){
    if (CheckBookClassificationExist(before)){
        vector<string> vec;
        vec.push_back("not-all");
        vec.push_back("isbn");
        vec.push_back("classification");
        if (db.update("book-classification", before, after, vec) != -1)
            return true;
        else
            return false;
    }else{
        return false;
    }
}

bool Utils::AddBook(Book book){
    if (InsertBook(book)){
        for (int i = 0; i < book.getStorage(); i ++){
            IsbnBookId ibi = IsbnBookId();
            ibi.setIsbn(book.getIsbn());
            ibi.setBookId(i);
            ibi.setIsBorrowed(0);
            ibi.setTimeBorrow("");
            ibi.setBorrowAccount("");
            if (!InsertIsbnBookId(ibi))
            {
                return false;
            }
        }
    }else{
        return false;
    }
}//参数为新增图书，函数使用条件：已判断书库中无此书，返回操作成功结果


bool Utils::RemoveBook(Book book){
    if (book.getLeft() != book.getStorage()){
        return false;
    }
    if(!DeleteBook(book))
        return false;

    vector<string> val;
    val.push_back("not-all");
    val.push_back("isbn");

    StudentBook sb = StudentBook();
    sb.setIsbn(book.getIsbn());
    vector<StudentBook> res;
    if (db.select("student-book", sb, val, res) != -1){
        if (db.Delete("student-book", sb, val) == -1)
            return false;
    }

    IsbnBookId ibi = IsbnBookId();
    ibi.setIsbn(book.getIsbn());
    if (db.Delete("isbn-book_id", ibi, val) == -1)
        return false;

    BookClassification bc = BookClassification();
    bc.setIsbn(book.getIsbn());
    if (db.Delete("book-classification", bc, val) == -1)
        return false;


    return true;
}//参数为删除图书，使用条件：书库中有此书，返回操作是否成功结果（失败的原因可能是有人在借书）

int Utils::Register(User user) //参数：学生对象，功能：注册新学生。返回值：0:账号已存在，1:注册成功, -1注册失败
{
    if (CheckUserExist(user))
        return 0;
    else{
        if (InsertUser(user))
            return 1;
        else
            return -1;
    }
}

int Utils::Login(char* account, char* password) //参数1:账号，参数2:密码，功能：用户登录。返回值：0:账户不存在；1:登陆成功；2:密码错误
{
    if (CheckUserExist(GetUser(account)))
    {
        User user = GetUser(account);
        if (strcmp(password, user.getPassword()))
            return 1;
        else
            return 2;
    }else{
        return 0;
    }
}

bool Utils::GetMarkRank(vector<Book>&result) //参数为存结果列表，返回图书列表对象，内容为按收藏数排序的前十个图书
{
    Rank rank;
    vector<string> value;
    value.push_back("all");
    vector<Rank> result_rank;
    int pos = db.select("mark_rank", rank, value, result_rank);
    if (pos != -1){
        Book book = Book();
        for (int i = 0; i < result_rank.size(); i ++ )
        {
            book = GetBook(result_rank.at(i).getIsbn());
            //coutbook.getIsbn()<<endl;
            result.push_back(book);
        }
        return true;
    }
    else
        return false;
}

bool Utils::GetBorrowRank(vector<Book>&result) //参数为存结果列表，返回图书列表对象，内容为按历史借阅总数排序的前十个图书
{
    Rank rank;
    vector<string> value;
    value.push_back("all");
    vector<Rank> result_rank;
    int pos = db.select("borrow_rank", rank, value, result_rank);
    if (pos != -1){
        Book book = Book();
        for (int i = 0; i < result_rank.size(); i ++ )
        {
            book = GetBook(result_rank.at(i).getIsbn());
            result.push_back(book);
        }
        return true;
    }
    else
        return false;
}


bool Utils::UpdateMarkRank(){
    vector<Book> result;
    vector<string> value;
    value.push_back("all");
    Book book = Book();
    if (db.select("book", book, value, result) != -1){
        for (int i = 0 ; i < result.size(); i ++ ){
            for (int j = 0; j < result.size() - 1 - i; j ++ ){
                if (result.at(j).getNumMark() < result.at(j + 1).getNumMark()){
                    swap(result.at(j), result.at(j + 1));
                }
            }
        }

        Rank rank_t = Rank();
        if (db.Delete("mark_rank", rank_t, value) != -1){
            vector<Rank> insert_list;
            for (int i = 0 ; i < result.size(); i ++) {
                Rank rank = Rank();
                rank.setIsbn(result.at(i).getIsbn());
                insert_list.push_back(rank);
            }
            if (db.insert("mark_rank", insert_list) != -1)
                return true;
            else
                return false;
        }else{
            return false;
        }
    }
    else {
        return false;
    }
} //更新收藏榜单，返回操作是否成功的结果。该操作需要管理员权限。


bool Utils::UpdateBorrowRank(){
    vector<Book> result;
    vector<string> value;
    value.push_back("all");
    Book book = Book();
    if (db.select("book", book, value, result) != -1){
        for (int i = 0 ; i < result.size(); i ++ ){
            for (int j = 0; j < result.size() - 1 - i ; j ++ ){
                if (result.at(j).getNumBorrow() < result.at(j + 1).getNumBorrow()){
                    swap(result.at(j), result.at(j + 1));
                }
            }
        }
        Rank rank_t = Rank();
        if (db.Delete("borrow_rank", rank_t, value) != -1){
            vector<Rank> insert_list;
            for (int i = 0 ; i < result.size(); i ++) {
                Rank rank = Rank();
                rank.setIsbn(result.at(i).getIsbn());
                insert_list.push_back(rank);
            }
            if (db.insert("borrow_rank", insert_list) != -1)
                return true;
            else
                return false;
        }else{
            return false;
        }
    }
    else {
        return false;
    }
} //更新历史借阅榜单，返回操作是否成功的结果。该操作需要管理员权限。

bool Utils::GetBooksByBookName(char* name, vector<Book>&result){
    vector<string> value;
    value.push_back("not-all");
    value.push_back("name");
    Book book = Book();
    book.setName(name);
    if (db.select("book", book, value, result) != -1)
        return true;
    else
        return false;
} //参数1为图书名，参数2为存结果列表，操作为根据书名检索图书，返回操作是否成功的结果


bool Utils::GetBooksByAuthor(char* author, vector<Book>&result){
    vector<string> value;
    value.push_back("not-all");
    value.push_back("author");
    Book book = Book();
    book.setAuthor(author);
    if (db.select("book", book, value, result) != -1)
        return true;
    else
        return false;
} //参数1为作者名，参数2为存结果列表，操作为根据作者名检索图书，返回操作是否成功的结果


Book Utils::GetBookByIsbn(char* isbn){
    return GetBook(isbn);
} //参数1为isbn，返回isbn对应图书对象


bool Utils::GetBooksByClassificationId(int classification_id, vector<Book>&result){
    vector<string> value;
    value.push_back("not-all");
    value.push_back("classification");
    BookClassification bc = BookClassification();
    bc.setClassification(classification_id);
    vector<BookClassification> res;
    if (db.select("book-classification", bc, value, res) != -1){
        for (int i =0; i < res.size(); i ++)
            result.push_back(GetBookByIsbn(res.at(i).getIsbn()));
        return true;
    }
    else
        return false;
} //参数1为分区id，参数2为存结果列表，操作为根据分区id检索图书，返回操作是否成功的结果


bool Utils::GetRecommendList(User user, vector<Book>&result){
    StudentBook sb = StudentBook();
    sb.setAccount(user.getAccount());
    sb.setRecommend(1);
    vector<string> vec;
    vec.push_back("not-all");
    vec.push_back("account");
    vec.push_back("recommend");
    vector<StudentBook> list;
    if (db.select("student-book", sb, vec, list) != -1){
        for (int i = 0; i < list.size(); i ++ ){
            result.push_back(GetBookByIsbn(list.at(i).getIsbn()));
        }
        return true;
    }else {
        if(result.size() == 0)return true;
        return false;
    }
} //参数1为User对象,参数2为存结果列表，返回值为该用户的推荐书目列表


bool Utils::UpdateRecommandList(User user){
    vector<Book> recommand_list;
    GetRecommendList(user, recommand_list);
    //将两个榜单的书加入推荐中
    vector<Book> mark_list;
    vector<Book> borrow_list;
    GetMarkRank(mark_list);
    GetBorrowRank(borrow_list);
    for (int i = 0 ; i < mark_list.size(); i ++ ){
        bool find = false;
        for (int j = 0; j < recommand_list.size(); j ++ ){
            if (strcmp(mark_list.at(i).getIsbn(), recommand_list.at(j).getIsbn()))
            {
                find = true;
                break;
            }
        }
        if (!find){
            StudentBook sb = StudentBook();
            sb.setAccount(user.getAccount());
            sb.setIsbn(mark_list.at(i).getIsbn());
            if (CheckStudentBookExist(sb))
            {
                sb = GetStudentBook(user.getAccount(), mark_list.at(i).getIsbn());
                StudentBook new_sb = sb;
                new_sb.setRecommend(1);
                if (!UpdateStudentBook(sb, new_sb))
                    return false;
            }else{
                sb.setMark(0);
                sb.setRecommend(1);
                sb.setIsAppointed(0);
                sb.setIsInBorrowedHistory(0);
                if (!InsertStudentBook(sb))
                    return false;
            }
        }
    }

    for (int i = 0 ; i < borrow_list.size(); i ++ ){
        bool find = false;
        for (int j = 0; j < recommand_list.size(); j ++ ){
            if (strcmp(borrow_list.at(i).getIsbn(), recommand_list.at(j).getIsbn()))
            {
                find = true;
                break;
            }
        }
        if (!find){
            StudentBook sb = StudentBook();
            sb.setAccount(user.getAccount());
            sb.setIsbn(borrow_list.at(i).getIsbn());
            if (CheckStudentBookExist(sb))
            {
                sb = GetStudentBook(user.getAccount(), borrow_list.at(i).getIsbn());
                StudentBook new_sb = sb;
                new_sb.setRecommend(1);
                if (!UpdateStudentBook(sb, new_sb))
                    return false;
            }else{
                sb.setMark(0);
                sb.setRecommend(1);
                sb.setIsAppointed(0);
                sb.setIsInBorrowedHistory(0);
                if (!InsertStudentBook(sb))
                    return false;
            }
        }
    }

    //将相同专业的同学的借书、收藏和预约推荐给该用户
    vector<User> same_user_list;
    vector<string> vec;
    vec.push_back("not-all");
    vec.push_back("major");
    if (db.select("user", user, vec, same_user_list)){
        for (int i = 0 ; i < same_user_list.size(); i ++ ){
            vector<IsbnBookId> borrowing_list;
            if (GetBorrowingList(same_user_list.at(i), borrowing_list)){
                StudentBook sb = StudentBook();
                sb.setAccount(user.getAccount());
                sb.setIsbn(borrowing_list.at(i).getIsbn());
                if (CheckStudentBookExist(sb))
                {
                    sb = GetStudentBook(user.getAccount(), borrowing_list.at(i).getIsbn());
                    StudentBook new_sb = sb;
                    new_sb.setRecommend(1);
                    if (!UpdateStudentBook(sb, new_sb))
                        return false;
                }else{
                    sb.setMark(0);
                    sb.setRecommend(1);
                    sb.setIsAppointed(0);
                    sb.setIsInBorrowedHistory(0);
                    if (!InsertStudentBook(sb))
                        return false;
                }
            }
            vector<Book> mark_list;
            if (GetMarkList(user, mark_list)){
                StudentBook sb = StudentBook();
                sb.setAccount(user.getAccount());
                sb.setIsbn(mark_list.at(i).getIsbn());
                if (CheckStudentBookExist(sb))
                {
                    sb = GetStudentBook(user.getAccount(), mark_list.at(i).getIsbn());
                    StudentBook new_sb = sb;
                    new_sb.setRecommend(1);
                    if (!UpdateStudentBook(sb, new_sb))
                        return false;
                }else{
                    sb.setMark(0);
                    sb.setRecommend(1);
                    sb.setIsAppointed(0);
                    sb.setIsInBorrowedHistory(0);
                    if (!InsertStudentBook(sb))
                        return false;
                }
            }
            vector<Book> appointment_list;
            if (GetAppointmentList(user, appointment_list)){
                StudentBook sb = StudentBook();
                sb.setAccount(user.getAccount());
                sb.setIsbn(appointment_list.at(i).getIsbn());
                if (CheckStudentBookExist(sb))
                {
                    sb = GetStudentBook(user.getAccount(), appointment_list.at(i).getIsbn());
                    StudentBook new_sb = sb;
                    new_sb.setRecommend(1);
                    if (!UpdateStudentBook(sb, new_sb))
                        return false;
                }else{
                    sb.setMark(0);
                    sb.setRecommend(1);
                    sb.setIsAppointed(0);
                    sb.setIsInBorrowedHistory(0);
                    if (!InsertStudentBook(sb))
                        return false;
                }
            }
        }
    }

    return true;

} //参数为用户对象，操作为更新对该用户的推荐图书


bool Utils::GetMarkList(User user, vector<Book>&result) //参数1为学生账号，参数2为存结果列表，返回该用户的收藏列表
{
    if (CheckUserExist(user)){

        StudentBook sb = StudentBook();
        sb.setAccount(user.getAccount());
        sb.setMark(1);
        vector<string> value;
        value.push_back("not-all");
        value.push_back("account");
        value.push_back("mark");
        vector<StudentBook> result_mark;
        if (db.select("student-book", sb, value, result_mark) != -1)
        {
            //cout"sdads";
            Book book = Book();
            for (int i = 0; i < result_mark.size(); i ++ )
            {
                book = GetBook(result_mark.at(i).getIsbn());
                result.push_back(book);
            }
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool Utils::GetBorrowingList(User user, vector<IsbnBookId>&result) //参数1为学生账号，参数2为存结果列表，返回该用户的正在借书列表
{
    if (CheckUserExist(user)){
        IsbnBookId ibi = IsbnBookId();
        ibi.setBorrowAccount(user.getAccount());
        ibi.setIsBorrowed(1);
        vector<string> value;
        value.push_back("not-all");
        value.push_back("borrow_account");
        value.push_back("isBorrowed");
        if (db.select("isbn-book_id", ibi, value, result) != -1)
            return true;
        else
            return false;
    }else{
        return false;
    }
}

bool Utils::GetAppointmentList(User user, vector<Book>&result) //参数1为学生账号，参数2为存结果列表，返回该用户预约的图书列表
{
    if (CheckUserExist(user)){
        StudentBook sb = StudentBook();
        sb.setAccount(user.getAccount());
        sb.setIsAppointed(1);
        vector<StudentBook> res;
        vector<string> value;
        value.push_back("not-all");
        value.push_back("account");
        value.push_back("isAppointed");
        //cout"dshhdsh"<<endl;
        if (db.select("student-book", sb, value, res) != -1){
            //cout"llllllllllll"<<endl;
            for (int i = 0 ; i < res.size(); i ++ ){
                result.push_back(GetBook(res.at(i).getIsbn()));
            }
            return true;
        }
        else
        {
            //cout"caoni"<<endl;
            return false;
        }
    }else{
        return false;
    }
}




bool Utils::CheckIfBookAppointed(Book book){
    StudentBook sb = StudentBook();
    sb.setIsbn(book.getIsbn());
    sb.setIsAppointed(1);
    vector<string> value;
    value.push_back("not-all");
    value.push_back("isbn");
    value.push_back("isAppointed");
    vector<StudentBook> res;
    if (db.select("student-book", sb, value, res) == -1)
        return false;
    else
        return true;
} //参数为图书对象，返回该书是否被预约


User Utils::GetAppointmentUser(Book book){
    StudentBook sb = StudentBook();
    sb.setIsbn(book.getIsbn());
    sb.setIsAppointed(1);
    vector<string> value;
    value.push_back("not-all");
    value.push_back("isbn");
    value.push_back("isAppointed");
    vector<StudentBook> res;
    if (db.select("student-book", sb, value, res) != -1)
        return GetUser(res.at(0).getAccount());
    else{
        User user = User();
        return user;
    }
} //参数为图书对象，返回对该类书的预约的唯一用户，默认该书已被预约


bool Utils::CheckIfBookIdBorrowed(Book book, int book_id){
    IsbnBookId ibi = GetIsbnBookId(book.getIsbn(), book_id);
    return ibi.getIsBorrowed();
} //参数1为图书对象,参数2为单本id，返回该书是否被借阅


User Utils::GetBorrowUser(Book book, int book_id){
    IsbnBookId ibi = GetIsbnBookId(book.getIsbn(), book_id);
    return GetUser(ibi.getBorrowAccount());
} //参数1为图书对象，参数2为单本Id,返回借阅这本书的用户


bool Utils::Borrow(User user, Book book, int book_id) //参数1:借书学生账号，参数2:所借图书唯一编号，参数3:借书id，返回操作是否成功
{
    //看是否有相应student-book文件，无则新增,有则更新isInBorrowedHistory和isAppointed
    StudentBook sb = StudentBook();
    sb.setAccount(user.getAccount());
    sb.setIsbn(book.getIsbn());
    if (!CheckStudentBookExist(sb)){
        sb.setMark(0);
        sb.setRecommend(0);
        sb.setIsInBorrowedHistory(1);
        sb.setIsAppointed(0);
        if (!InsertStudentBook(sb)){
            return false;
        }
        cout<<"insert the bc data "<<endl;
    }else {
        sb = GetStudentBook(user.getAccount(), book.getIsbn());
        StudentBook new_sb = sb;
        new_sb.setIsInBorrowedHistory(1);
        if (CheckIfBookAppointed(book))
        {
            new_sb.setIsAppointed(0);
        }
        if (!UpdateStudentBook(sb, new_sb))
            return false;
        cout<<"update the bc data"<<endl;
    }

    //更新isbn-book_id文件
    IsbnBookId ibi = GetIsbnBookId(book.getIsbn(), book_id);
    IsbnBookId new_ibi = ibi;
    new_ibi.setIsBorrowed(1);
    QDateTime mDate = QDateTime::currentDateTime();
    new_ibi.setTimeBorrow(mDate.time().toString("yyyy-MM-dd").toStdString().c_str());
    new_ibi.setBorrowAccount(user.getAccount());


    vector<IsbnBookId> vec15;
    if(GetBookIdsOfBook(book, vec15)){
        cout << "........................pos1.5                "<<vec15.size()<<endl;
    }
    if (!UpdateIsbnBookId(ibi, new_ibi)){
        return false;
    }else{
        cout<<"update ibi success"<<endl;
    }

    vector<IsbnBookId> vec16;
    if(GetBookIdsOfBook(book, vec16)){
        cout << "........................pos1.6                "<<vec16.size()<<endl;
    }

    //更新Book文件，修改剩余量和历史总借阅数
    Book new_book = book;
    //cout"in borrow, book.getLeft"<<book.getLeft()<<endl;
    new_book.setLeft(book.getLeft() - 1);
    new_book.setNumBorrow(book.getNumBorrow() + 1);
    if (!UpdateBook(book, new_book))
        return false;

    return true;
}

bool Utils::Return(User user, Book book, int book_id) //参数1:还书学生账号，参数2:所还图书唯一编号，参数3:还书id，返回操作是否成功
{
    //更新book
    Book new_book = book;
    new_book.setLeft(book.getLeft() + 1);
    QDateTime mDate = QDateTime::currentDateTime();
    new_book.setAvailableAppointmentTime(mDate.time().toString("yyyy-MM-dd").toStdString().c_str());
    //cout"1111"<<endl;
    if (UpdateBook(book, new_book)){
        //更新isbn-book_id

        IsbnBookId ibi = GetIsbnBookId(book.getIsbn(), book_id);
        IsbnBookId new_ibi = ibi;
        new_ibi.setIsBorrowed(0);

        if (!UpdateIsbnBookId(ibi, new_ibi)){
            return false;
        }
        return true;
    }else{
        return false;
    }

}

bool Utils::Appoint(User user, Book book) //参数1:续借学生账号，参数2:所借图书唯一编号，返回操作是否成功
{
    //更新student-book文件
    StudentBook sb = StudentBook();
    sb.setAccount(user.getAccount());
    sb.setIsbn(book.getIsbn());
    if (CheckStudentBookExist(sb)){
        sb = GetStudentBook(user.getAccount(), book.getIsbn());
        StudentBook new_sb = sb;
        new_sb.setIsAppointed(1);
        new_sb.setRecommend(1);
        //cout"comeafdafjd";
        if (!UpdateStudentBook(sb, new_sb))
            return false;
    }else{
        //cout"in yuyue........................................................."<<endl;
        sb.setMark(0);
        sb.setRecommend(1);
        sb.setIsInBorrowedHistory(0);
        sb.setIsAppointed(1);
        if (!InsertStudentBook(sb))
            return false;
    }
    return true;
}

bool Utils::PreAppoint(User user, Book book){
    //更新student-book文件
    StudentBook sb = GetStudentBook(user.getAccount(), book.getIsbn());
    StudentBook new_sb = sb;
    new_sb.setIsAppointed(0);
    new_sb.setRecommend(1);
    if (!UpdateStudentBook(sb, new_sb))
        return false;;
    return true;
} //参数1:取消预约者用户，参数2:所取消预约图书isbn,返回操作是否成功

bool Utils::GetBookIdsOfBook(Book book, vector<IsbnBookId>&result){
    IsbnBookId ibi = IsbnBookId();
    ibi.setIsbn(book.getIsbn());
    vector<string> value;
    value.push_back("not-all");
    value.push_back("isbn");
    if (db.select("isbn-book_id", ibi, value, result)== -1)
        return false;
    return true;
} //参数1为Book对象， 参数2为存结果列表，即该isbn所对应isbn-book_id文件中所有条目，返回操作是否成功的结果

bool Utils::SetMark(User user, Book book, int isMark) //参数1:收藏者的账号，参数2:所收藏图书isbn，参数3:加入收藏true取消收藏false， 返回操作是否成功
{
   //更新book
   Book new_book = book;
   if (isMark == 1){
       new_book.setNumMark(book.getNumMark() + 1);
   }else{
       new_book.setNumMark(book.getNumMark() - 1);
   }
   if (!UpdateBook(book, new_book))
       return false;

   //新增或者更新student-book条目
   StudentBook sb = StudentBook();
   sb.setAccount(user.getAccount());
   sb.setIsbn(book.getIsbn());
   if (CheckStudentBookExist(sb)){
       sb = GetStudentBook(user.getAccount(), book.getIsbn());
       StudentBook new_sb = sb;
       new_sb.setMark(isMark);
       new_sb.setRecommend(1);
       if (!UpdateStudentBook(sb, new_sb))
           return false;
   }else {
       sb.setMark(isMark);
       sb.setRecommend(1);
       sb.setIsInBorrowedHistory(0);
       sb.setIsAppointed(0);
       if (!InsertStudentBook(sb))
           return false;
   }
   return true;
}

bool Utils::GetBooksOfClassification(int classification_id, vector<Book>&result) //参数1为分区ID,参数2为存结果列表，返回操作是否成功
{
    BookClassification bc = BookClassification();
    bc.setClassification(classification_id);
    vector<string> value;
    value.push_back("not-all");
    value.push_back("classification");
    vector<BookClassification> res;
    if (db.select("book-classification", bc, value, res) != -1) {
        Book book;
        for (int i = 0; i < res.size(); i ++ )
        {
            book = GetBook(res.at(i).getIsbn());
            result.push_back(book);
        }
        //coutbook.getName()<<endl;
        return true;
    }else {
        return false;
    }
}

bool Utils::GetClassificationsOfBook(Book book, vector<int>&result) //参数为1为图书isbn，参数2为所属分区id存储列表，返回操作是否成功的结果
{
    BookClassification bc = BookClassification();
    bc.setIsbn(book.getIsbn());
    vector<string> value;
    value.push_back("not-all");
    value.push_back("isbn");
    vector<BookClassification> res;
    if (db.select("book-classification", bc, value, res) != -1) {
        for (int i = 0; i < res.size(); i ++ )
        {
            result.push_back(res.at(i).getClassification());
        }
        return true;
    }else {
        return false;
    }
}


bool Utils::CheckAdmin(User user){
    return user.getIsAdmin();
} //参数为User对象，返回该用户是否是管理员，是true，不是false


bool Utils::CheckIsFrooze(User user){
    return user.getFrooze();
} //参数为用户对象，返回该用户是否被冻结的结果


bool Utils::SetUserFrooze(User user, int frooze){
    User new_user = user;
    new_user.setFrooze(frooze);
    if (UpdateUser(user, new_user))
        return true;
    else
        return false;
} //参数1为用户对象，参数2为设置用户的冻结状态，1冻结2不冻结，返回操作是否成功的结果


int Utils::TransformClassification(QString str){

    map<QString,int>mp;
    mp.insert({"哲学",0});
    mp.insert({"人文社科综合",1});
    mp.insert({"管理学",2});
    mp.insert({"政治",3});
    mp.insert({"法律",4});
    mp.insert({"经济",5});
    mp.insert({"文化/教育",6});
    mp.insert({"语言/文学",7});
    mp.insert({"艺术",8});
    mp.insert({"历史",9});
    mp.insert({"数学",10});
    mp.insert({"物理",11});
    mp.insert({"化学/材料",12});
    mp.insert({"理工综合",13});
    mp.insert({"地球科学",14});
    mp.insert({"生物",15});
    mp.insert({"医学/药学",16});
    mp.insert({"农业/水产",17});
    mp.insert({"工业技术",18});
    mp.insert({"计算机/网络",19});
    mp.insert({"环境",20});
    mp.insert({"其他",21});

    if(mp.find(str)==mp.end())return -1;
    else return mp[str];


} //参数为分区的名称，返回分区编号


bool Utils::RemoveUser(User user){
    if (!CheckUserExist(user)) return false;
    IsbnBookId ibi = IsbnBookId();
    ibi.setBorrowAccount(user.getAccount());
    ibi.setIsBorrowed(1);
    vector<string> value;
    value.push_back("not-all");
    value.push_back("borrow_account");
    value.push_back("isBorrowed");
    vector<IsbnBookId> res;
    if (db.select("isbn-book_id", ibi, value, res) != -1)//成功查找，说明该用户仍有借书，不能删除
        return false;
    else{
        if (!DeleteUser(user)) return false;
        StudentBook sb = StudentBook();
        sb.setAccount(user.getAccount());
        vector<string> value;
        value.push_back("not-all");
        value.push_back("account");
        if (db.Delete("student-book", sb, value) != -1)//删除student-book中的数据
            return true;
        else
            return false;
    }
}

bool Utils::GetUserByName(char* name, vector<User>&result){
    User user = User();
    user.setName(name);
    vector<string> val;
    val.push_back("not-all");
    val.push_back("name");
    if (db.select("user", user, val, result) != -1)
        return true;
    else
        return false;
}

bool Utils::GetUserByMajor(char *major, vector<User> &result){
    User user = User();
    user.setMajor(major);
    vector<string> val;
    val.push_back("not-all");
    val.push_back("major");
    if (db.select("user", user, val, result) != -1)
        return true;
    else
        return false;
}
