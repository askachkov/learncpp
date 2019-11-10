TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    asio_thread_pool.cpp

HEADERS += \
    asio_thread_pool.h

BOOST_DIR="D:/Boost"

LIBS += -L$$BOOST_DIR/lib/ -llibboost_date_time-vc120-mt-x32-1_71

INCLUDEPATH += $$BOOST_DIR/include/boost-1_71
DEPENDPATH += $$BOOST_DIR/include/boost-1_71
