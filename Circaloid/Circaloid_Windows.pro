TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += core

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

INCLUDEPATH += C:\Qt\sfml\include


LIBS += -LC:\Qt\sfml\lib
LIBS += -LC:\Qt\sfml\bin

LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SOURCES += main.cpp \
    bullet.cpp \
    tohoid.cpp \
    menu.cpp \
    functions.cpp \
    seeker.cpp \
    game.cpp \
    tophics.cpp \
    choice.cpp \
    todio.cpp



HEADERS += \
    bullet.h \
    tohoid.h \
    menu.h \
    functions.h \
    seeker.h \
    game.h \
    tophics.h \
    choice.h \
    todio.h

RESOURCES += \
    resources.qrc

