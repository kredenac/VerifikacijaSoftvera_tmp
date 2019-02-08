TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    string_distance.cpp

HEADERS += \
    string_distance.h

QMAKE_CXXFLAGS += -g -O0 -fprofile-arcs -ftest-coverage
QMAKE_LFLAGS += -g -O0 -fprofile-arcs -ftest-coverage

