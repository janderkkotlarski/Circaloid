TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    simulation.cpp \
    bullet.cpp \
    functions.cpp \
    menu.cpp \
    tohoid.cpp \
    seeker.cpp

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra

INCLUDEPATH += D:/SFML-2.4.0/include

LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LIBS += -LD:/SFML-2.4.0/lib
LIBS += -LD:\SFML-2.4.0\bin


HEADERS += \
    simulation.h \
    bullet.h \
    functions.h \
    tohoid.h \
    menu.h \
    seeker.h

SUBDIRS += \
    Circaloid_Windows_DJOG.pro \
    Circaloid_Windows.pro

OTHER_FILES += \
    Circaloid_Linux.pro.user

