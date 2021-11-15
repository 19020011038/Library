QT       += core gui
QT += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#CONFIG += console

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    PageT.cpp \
    PageTable.cpp \
    PageWidget.cpp \
    add_book.cpp \
    admin.cpp \
    book_addonly.cpp \
    book_ditails.cpp \
    book_information.cpp \
    book_rank.cpp \
    books_add.cpp \
    borrowing.cpp \
    change_information.cpp \
    collection.cpp \
    formuser.cpp \
    loadpage.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    manager_interface.cpp \
    modify_book.cpp \
    modify_student.cpp \
    partition.cpp \
    person.cpp \
    preborrow.cpp \
    read_excel.cpp \
    regi.cpp \
    search_book.cpp \
    searchandselect.cpp \
    setting.cpp \
    test.cpp \
    tool.cpp \
    user_addonly.cpp \
    user_main.cpp \
    user_page.cpp \
    users_add.cpp \
    usertemplate.cpp

HEADERS += \
    ../../Documents/Tencent Files/1459987672/FileRecv/filedb.h \
    PageT.h \
    PageTable.h \
    PageWidget.h \
    add_book.h \
    admin.h \
    all_file_classes.h \
    book-classification.h \
    book.h \
    book_addonly.h \
    book_ditails.cpp.autosave \
    book_ditails.h \
    book_information.h \
    book_rank.h \
    books_add.h \
    borrowing.h \
    change_information.h \
    collection.h \
    config.h \
    filedb.h \
    formuser.h \
    isbn-book_id.h \
    isbn-student.h \
    loadpage.h \
    mainwindow.h \
    manager.h \
    manager_interface.h \
    modify_book.h \
    modify_student.h \
    partition.h \
    person.h \
    preborrow.h \
    rank.h \
    read_excel.h \
    regi.h \
    search_book.h \
    searchandselect.h \
    setting.h \
    student-book.h \
    test.h \
    tool.h \
    user.h \
    user_addonly.h \
    user_main.h \
    user_page.h \
    users_add.h \
    usertemplate.h

FORMS += \
    PageWidget.ui \
    add_book.ui \
    admin.ui \
    book_addonly.ui \
    book_ditails.ui \
    book_information.ui \
    book_rank.ui \
    books_add.ui \
    borrowing.ui \
    change_information.ui \
    collection.ui \
    formuser.ui \
    loadpage.ui \
    mainwindow.ui \
    manager.ui \
    manager_interface.ui \
    modify_book.ui \
    modify_student.ui \
    partition.ui \
    person.ui \
    preborrow.ui \
    regi.ui \
    search_book.ui \
    searchandselect.ui \
    setting.ui \
    template_user.ui \
    test.ui \
    user_addonly.ui \
    user_main.ui \
    user_page.ui \
    users_add.ui \
    usertemplate.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    8425E4451C8D4D0482C7E63E3A030A36-1603353108971.zip \
    A727F9CA7CDB490D93259A7619645C6C-1615343740257.zip \
    AB42B0B9AF3643CBACF2A3A5C3C565FC-1624853990331.zip \
    D03F9B006E30432A8F02E980E2945012-1625987686259.zip \
    Library.pro.user \
    Library.pro.user.469d927 \
    Library.pro.user.4aa1b3a \
    Library.pro.user.bd0c84e \
    admin_test.pro.user \
    admin_test.pro.user.4.8-pre1 \
    back.png \
    back2.png \
    bgimg.png \
    new_test.pro.user \
    new_test.pro.user.4aa1b3a \
    new_test.pro.user.bd0c84e.4.8-pre1 \
    test.png \
    千图网_9可编辑矢量线图标和现代符号的提交，出，购物，id，身份证矢量图_图片编号37506847.zip \
    千图网_套在主题用户的图标矢量图_图片编号38336822.zip \
    千图网_矢量书本图书图书馆书架icon图标_图片编号40256021.zip \
    单本添加.png \
    图书.png \
    批量添加.png \
    提交.png \
    用户.png \
    白钥匙.png \
    返回.png \
    钥匙.png


SUBDIRS += \
    admin_test.pro \
    admin_test.pro \
    admin_test.pro \
    admin_test.pro \
    admin_test.pro \
    new_test.pro \
    new_test.pro \
    new_test.pro \
    new_test.pro \
    new_test.pro \
    new_test.pro

QMAKE_CXXFLAGS += /utf-8

RESOURCES += \
    img_need.qrc
