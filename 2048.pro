#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T01:28:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 2048
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    grid.cpp \
    gridlogic.cpp

HEADERS  += mainwindow.h \
    grid.h \
    gridlogic.h

RESOURCES += \
    resource.qrc
