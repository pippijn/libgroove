QT += network \
    gui \
    phonon
TARGET = groovy-uic
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
unix:LIBS += ../libgroove/libgroove.so
win32:LIBS += ../libgroove/libgroove.dll

# Sources
HEADERS += ../../include/frontend/uic/preferences.h \
    ../../include/frontend/uic/groovewindow.h \
    ../../include/frontend/uic/about.h
SOURCES += ../../src/frontend/uic/preferences.cpp \
    ../../src/frontend/uic/main.cpp \
    ../../src/frontend/uic/groovewindow.cpp \
    ../../src/frontend/uic/debug.cpp \
    ../../src/frontend/uic/crash.cpp \
    ../../src/frontend/uic/about.cpp
FORMS += ../../src/uic/preferences.ui \
    ../../src/uic/groovewindow.ui \
    ../../src/uic/about.ui
