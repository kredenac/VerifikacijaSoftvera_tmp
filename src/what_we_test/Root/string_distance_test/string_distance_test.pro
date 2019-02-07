#-------------------------------------------------
#
# Project created by QtCreator 2018-05-24T04:25:49
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_string_distance_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -O0 -fprofile-arcs -ftest-coverage
QMAKE_LFLAGS += -O0 -fprofile-arcs -ftest-coverage

SOURCES += tst_string_distance_test.cpp \
    ../String_distance/string_distance.cpp

HEADERS += \
    ../String_distance/string_distance.h
