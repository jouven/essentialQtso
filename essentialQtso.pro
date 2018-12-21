#message($$QMAKESPEC)
QT -= gui

TARGET = essentialQtso
TEMPLATE = lib

!android:QMAKE_CXXFLAGS += -std=c++17
android:QMAKE_CXXFLAGS += -std=c++14

CONFIG += no_keywords plugin
#(only windows) fixes the extra tier of debug and release build directories inside the first build directories
win32:CONFIG -= debug_and_release

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += ESSENTIALQTSO_LIBRARY

SOURCES += \
    essentialQt.cpp \
    filenaming.cpp

HEADERS += \
    essentialQt.hpp \
    filenaming.hpp \
    macros.hpp \
    crossPlatformMacros.hpp

!win32:MYPATH = "/"
win32:MYPATH = "H:/veryuseddata/portable/msys64/"

QMAKE_CXXFLAGS_DEBUG -= -g
QMAKE_CXXFLAGS_DEBUG += -pedantic -Wall -Wextra -g3

linux:QMAKE_CXXFLAGS_RELEASE += -flto=jobserver
win32:QMAKE_CXXFLAGS_RELEASE += -flto
!android:QMAKE_CXXFLAGS_RELEASE += -mtune=sandybridge

#for -flto=jobserver in the link step to work with -jX
linux:!android:QMAKE_LINK = +g++

linux:QMAKE_LFLAGS += -fuse-ld=gold
QMAKE_LFLAGS_RELEASE += -fvisibility=hidden

linux:QMAKE_LFLAGS_RELEASE += -flto=jobserver
win32:QMAKE_LFLAGS_RELEASE += -flto
