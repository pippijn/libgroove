# -------------------------------------------------
# Project created by QtCreator 2010-09-22T21:46:16
# -------------------------------------------------
QT += network \
    gui \
    phonon
TARGET = groovy
TEMPLATE = app
INCLUDEPATH = ../../include/
DEPENDPATH = ../../include/

# qmake config
CONFIG += link_prl

# Flags
QMAKE_CXXFLAGS += -std=c++0x

# Defines
DEFINES += PACKAGE=\'\"groovy\"\'
DEFINES += PACKAGE_NAME=\'\"Groovy\"\'
DEFINES += PACKAGE_VERSION=\'\"0.1\"\'
DEFINES += PACKAGE_BUGREPORT=\'\"groovy@xinutec.org\"\'
DEFINES += PKGDATADIR=\'\"/path/to/data\"\'

# Extra libs
unix:LIBS += ../../libgroove/obj/libgroove.so
win32:LIBS += ../../libgroove/obj/libgroove.dll

# Sources
HEADERS += ../../include/preferences.h \
    ../../include/groovewindow.h \
    ../../include/about.h
SOURCES += ../../src/groovy/preferences.cpp \
    ../../src/groovy/main.cpp \
    ../../src/groovy/groovewindow.cpp \
    ../../src/groovy/debug.cpp \
    ../../src/groovy/crash.cpp \
    ../../src/groovy/about.cpp
FORMS += ../../src/ui/preferences.ui \
    ../../src/ui/groovewindow.ui \
    ../../src/ui/about.ui
