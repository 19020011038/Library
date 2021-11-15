#-------------------------------------------------
#
# Project created by QtCreator 2021-10-21T22:43:20
#
#-------------------------------------------------

QT       += core gui
QT += axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = new_test
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
    borrowing.cpp \
    change_information.cpp \
    collection.cpp \
    person.cpp \
    preborrow.cpp \
    read_excel.cpp \
    setting.cpp \
    tool.cpp

HEADERS += \
        mainwindow.h \
    book.h \
    borrowing.h \
    change_information.h \
    collection.h \
    config.h \
    filedb.h \
    isbn-book_id.h \
    person.h \
    preborrow.h \
    rank.h \
    read_excel.h \
    setting.h \
    student-book.h \
    tool.h \
    user.h \
    all_file_classes.h \
    book-classification.h

FORMS += \
        mainwindow.ui \
    borrowing.ui \
    change_information.ui \
    collection.ui \
    person.ui \
    preborrow.ui \
    setting.ui

QMAKE_CXXFLAGS += /utf-8
