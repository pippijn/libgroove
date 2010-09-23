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
unix:LIBS += ../../libgroove/libgroove.so
win32:LIBS += ../../libgroove/libgroove.dll

# Sources
include(../source-common/source-common.pro)
include(../ui-common/ui-common.pro)
