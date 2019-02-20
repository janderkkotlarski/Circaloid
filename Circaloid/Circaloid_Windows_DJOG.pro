TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    simulation.cpp \
    bullet.cpp \
    tohoid.cpp \
    menu.cpp \
    functions.cpp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

INCLUDEPATH += C:\Qt\sfml\include

LIBS += -LC:/Qt/sfml/lib
LIBS += -LC:\Qt\sfml\bin
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

HEADERS += \
    simulation.h \
    bullet.h \
    tohoid.h \
    menu.h \
    functions.h

