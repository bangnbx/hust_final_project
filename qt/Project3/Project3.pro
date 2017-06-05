#-------------------------------------------------
#
# Project created by QtCreator 2016-12-12T21:11:02
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    createuserwindow.cpp \
    verifywindow.cpp \
    finger.cpp \
    identifywindow.cpp \
    mysqldb.cpp \
    userwindow.cpp

HEADERS  += mainwindow.h \
    createuserwindow.h \
    verifywindow.h \
    finger.h \
    identifywindow.h \
    mysqldb.h \
    userwindow.h

FORMS    += mainwindow.ui \
    createuserwindow.ui \
    verifywindow.ui \
    identifywindow.ui \
    userwindow.ui


LIBS    +=  -lfprint \
    -lmysqlclient
