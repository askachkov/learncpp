TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    server_impl.cpp \
    logger.cpp \
    session.cpp

DEFINES+=BOOST_LIB_DIAGNOSTIC

BOOST_DIR="D:/Boost"

LIBS += -L$$BOOST_DIR/lib/ -llibboost_date_time-vc120-mt-gd-x32-1_71

INCLUDEPATH += $$BOOST_DIR/include/boost-1_71
DEPENDPATH += $$BOOST_DIR/include/boost-1_71


HEADERS += \
    server_impl.h \
    logger.h \
    types.h \
    session.h \
    message.h

DISTFILES += \
    room/1.txt

