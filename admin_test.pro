#-------------------------------------------------
#
# Project created by QtCreator 2021-10-22T16:18:19
#
#-------------------------------------------------

QT       += core gui
QT += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = admin_test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    modify_book.cpp \
    modify_student.cpp \
    read_excel.cpp \
    tool.cpp \
    add_book.cpp \
    admin.cpp \
    book_addonly.cpp \
    books_add.cpp \
    user_addonly.cpp \
    users_add.cpp

HEADERS += \
        mainwindow.h \
    all_file_classes.h \
    book.h \
    book-classification.h \
    config.h \
    filedb.h \
    isbn-book_id.h \
    isbn-student.h \
    modify_book.h \
    modify_student.h \
    rank.h \
    read_excel.h \
    student-book.h \
    tool.h \
    user.h \
    add_book.h \
    admin.h \
    book_addonly.h \
    books_add.h \
    user_addonly.h \
    users_add.h

FORMS += \
        mainwindow.ui \
    add_book.ui \
    admin.ui \
    book_addonly.ui \
    books_add.ui \
    modify_book.ui \
    modify_student.ui \
    user_addonly.ui \
    users_add.ui

QMAKE_CXXFLAGS += /utf-8
