TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    simulation.cpp \
    bullet.cpp \
    tohoid.cpp \
    menu.cpp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

INCLUDEPATH += D:\SFML-2.4.0\include

LIBS += -LD:/SFML-2.4.0/lib
LIBS += -LD:\SFML-2.4.0\bin
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

HEADERS += \
    simulation.h \
    bullet.h \
    tohoid.h \
    menu.h

