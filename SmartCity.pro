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
        mainwindow.cpp \
    algothread.cpp \
    paramlist.cpp \
    GUI/camion.cpp \
    GUI/people.cpp \
    GUI/place.cpp

HEADERS  += mainwindow.h \
    algothread.h \
    paramlist.h \
    GUI/camion.h \
    GUI/people.h \
    GUI/place.h

FORMS    += mainwindow.ui \
    GUI/camion.ui \
    GUI/people.ui \
    GUI/place.ui

RESOURCES += \
    icon.qrc

DISTFILES += \
    img/bike.png \
    img/camion.png \
    img/people_action.png \
    img/people_bike.png \
    img/people_wait.png \
    img/place.png
