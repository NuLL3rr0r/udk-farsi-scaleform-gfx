#-------------------------------------------------
#
# Project created by QtCreator 2011-06-02T18:58:13
#
#-------------------------------------------------

QT       += core gui sql

TARGET = TextGenerator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        ../../lib/sqlite3.c \
        ../../lib/text2flash.cpp

HEADERS  += mainwindow.h \
        ../../lib/sqlite3.h \
        ../../lib/text2flash.hpp

FORMS    += mainwindow.ui
