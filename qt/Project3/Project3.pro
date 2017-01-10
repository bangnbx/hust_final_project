#-------------------------------------------------
#
# Project created by QtCreator 2016-12-12T21:11:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    createuserwindow.cpp \
    verifywindow.cpp \
    finger.cpp \
    identifywindow.cpp

HEADERS  += mainwindow.h \
    createuserwindow.h \
    verifywindow.h \
    finger.h \
    identifywindow.h

FORMS    += mainwindow.ui \
    createuserwindow.ui \
    verifywindow.ui \
    identifywindow.ui

LIBS    +=  -lfprint \
    -lmysqlclient
