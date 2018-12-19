#-------------------------------------------------
#
# Project created by QtCreator 2017-10-08T16:02:23
#
#-------------------------------------------------

QT       += core gui
QT       += testlib
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ODA-IDE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# Code editor
# felület ahol lehet editálni
# fájl böngésző oldalt
# save / load / load last
# compile / build
# file extension felismerés. java, python, C, C++, arduino
# run
# syntax highlight

TEST = 1

SOURCES += \
    src/console.cpp \
    src/editor.cpp \
    src/filemanager.cpp \
    src/highlighter.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/tab.cpp \
    src/test.cpp \
    src/settings.cpp \
    src/settingsdialog.cpp \
    sqlhandler.cpp


   # src/settingsdialog.cpp\
  #  src/intellisense.cpp
  #  src/test/testeditor.cpp \

HEADERS += \
    Headers/console.h \
    Headers/editor.h \
    Headers/filemanager.h \
    Headers/highlighter.h \
    Headers/mainwindow.h \
    Headers/tab.h \
    Headers/settings.h \
    Headers/settingsdialog.h \
    sqlhandler.h


  #  Headers/settingsdialog.h \
 #   Headers/intellisense.h
    #Headers/testeditor.h \


DISTFILES +=

CONFIG += testcase

FORMS += \
    settingsdialog.ui


