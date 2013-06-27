QT += network \
    declarative \
    phonon
TARGET = groovy-qml
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
SOURCES += ../../src/frontend/qml/main.cpp

# Resources
RESOURCES += ../../res/qml.qrc \
    ../../res/symbols.qrc
