#-------------------------------------------------
#
# Project created by QtCreator 2016-12-03T22:07:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = weatherScada
TEMPLATE = app

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/protocol.cpp \
    src/func.cpp \
    src/sysconfig.cpp

HEADERS  += inc/mainwindow.h \
    inc/protocol.h \
    inc/basedef.h \
    inc/func.h \
    inc/sysconfig.h

INCLUDEPATH += 	inc

FORMS    += ui/mainwindow.ui

RESOURCES += weatherScada.qrc

DESTDIR  = obj/
