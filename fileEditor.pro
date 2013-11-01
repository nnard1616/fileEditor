TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11
SOURCES += \
    test.cpp \
    helperFunctions.cpp \
    editTracker.cpp \
    ui.cpp

HEADERS += \
    helperFunctions.h \
    editTracker.h \
    ui.h

