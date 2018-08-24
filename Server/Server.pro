#-------------------------------------------------
#
# Project created by QtCreator 2017-12-12T19:43:19
#
#-------------------------------------------------

QT       += core gui network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    TcpSocket.cpp \
    server.cpp \
    udpclient.cpp \
    ServerQuitMsg.cpp

HEADERS  += mainwindow.h \
    TcpSocket.h \
    server.h \
    udpclient.h \
    ServerQuitMsg.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
