#-------------------------------------------------
#
# Project created by QtCreator 2017-11-29T17:57:37
#
#-------------------------------------------------

QT       += core gui network multimedia
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TankWar1_8
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tankclient.cpp \
    runthread.cpp \
    global.cpp \
    tank.cpp \
    missile.cpp \
    pt.cpp \
    Explode.cpp \
    Wall/Wall.cpp \
    NetClient.cpp \
    connect_dialog.cpp \
    tanknewmsg.cpp \
    TankMoveMsg.cpp \
    MissileNewMsg.cpp \
    TankDeadMsg.cpp \
    MissileDeadMsg.cpp \
    AppQuitMsg.cpp

HEADERS  += mainwindow.h \
    tankclient.h \
    runthread.h \
    global.h \
    tank.h \
    missile.h \
    pt.h \
    Explode.h \
    Wall/Wall.h \
    NetClient.h \
    connect_dialog.h \
    Msg.h \
    tanknewmsg.h \
    TankMoveMsg.h \
    MissileNewMsg.h \
    TankDeadMsg.h \
    MissileDeadMsg.h \
    AppQuitMsg.h

FORMS    += mainwindow.ui \
    tankclient.ui \
    connect_dialog.ui

DISTFILES += \
    TankWar1_8.pro.user.3d60a31 \
    TankWar1_8.pro.user.f872349

RESOURCES += \
    res.qrc
