TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

#CONFIG += c++17

SOURCES += main.cpp \
    variant.cpp

HEADERS += \
    weak_ptr.h \
    unique_ptr.h \
    shared_ptr.h \
    variant.h \
    field.h \
    sfinae.h

