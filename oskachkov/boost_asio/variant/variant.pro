TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    variant.cpp \
    serializer.cpp \
    json.cpp

HEADERS += \
    variant.h \
    serializer.h \
    json.h

