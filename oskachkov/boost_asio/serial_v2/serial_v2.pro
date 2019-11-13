TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    searchdev.cpp

HEADERS += \
    searchdev.h

BOOST_DIR="C:/Boost"

LIBS += -L$$BOOST_DIR/lib/ -lboost_date_time-vc120-mt-x32-1_71

INCLUDEPATH += $$BOOST_DIR/include/boost-1_71
DEPENDPATH += $$BOOST_DIR/include/boost-1_71
