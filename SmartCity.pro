#-------------------------------------------------
#
# Project created by QtCreator 2018-02-16T10:47:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartCity
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


SOURCES += main.cpp\
    algothread.cpp \
    paramlist.cpp \
    GUI/camion.cpp \
    GUI/people.cpp \
    GUI/place.cpp \
    habitant.cpp \
    maintenance.cpp \
    initwidget.cpp \
    citywidget.cpp \
    mainwindow.cpp

HEADERS  += \
    algothread.h \
    paramlist.h \
    GUI/camion.h \
    GUI/people.h \
    GUI/place.h \
    habitant.h \
    maintenance.h \
    initwidget.h \
    citywidget.h \
    mainwindow.h

FORMS    += \
    GUI/camion.ui \
    GUI/people.ui \
    GUI/place.ui \
    initwidget.ui

RESOURCES += \
    icon.qrc

DISTFILES += \
    img/bike.png \
    img/camion.png \
    img/people_action.png \
    img/people_bike.png \
    img/people_wait.png \
    img/place.png
