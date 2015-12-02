QT += core
QT -= gui
QT += network

TARGET = JuniorTask
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    processor.cpp

HEADERS += \
    processor.h

