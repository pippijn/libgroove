# -------------------------------------------------
# Project created by QtCreator 2010-09-22T21:46:16
# -------------------------------------------------
QT += network \
    gui \
    phonon
TARGET = Groovy
TEMPLATE = app
INCLUDEPATH = include/
DEPENDPATH = include/

# Flags
QMAKE_CXXFLAGS += -std=c++0x

# QJson library
CONFIG += link_pkgconfig
PKGCONFIG += QJson \
    log4cpp

# Defines
DEFINES += PACKAGE=\'\"groovy\"\'
DEFINES += PACKAGE_NAME=\'\"Groovy\"\'
DEFINES += PACKAGE_VERSION=\'\"0.1\"\'
DEFINES += PACKAGE_BUGREPORT=\'\"groovy@xinutec.org\"\'
DEFINES += PKGDATADIR=\'\"/path/to/data\"\'

# Sources
HEADERS += include/preferences.h \
    include/libgroove_global.h \
    include/groovewindow.h \
    include/about.h \
    include/groove/settings.h \
    include/groove/service.h \
    include/groove/fetcher.h \
    include/groove/client.h \
    include/groove/songsmodel.h \
    include/groove/data/userptr.h \
    include/groove/data/user.h \
    include/groove/data/songptr.h \
    include/groove/data/song.h \
    include/groove/data/playlistptr.h \
    include/groove/data/playlist.h \
    include/groove/data/artistptr.h \
    include/groove/data/artist.h \
    include/groove/data/albumptr.h \
    include/groove/data/album.h \
    include/groove/private/make_varmap.h \
    src/libgroove_service/request.h \
    src/libgroove_client/private.h \
    include/property/prop.h \
    include/property/value_prop.h \
    include/property.h \
    include/groove/searchmodel.h \
    include/groove/playlistmodel.h \
    src/libgroove_client/client-request.h
SOURCES += src/groovy/preferences.cpp \
    src/groovy/main.cpp \
    src/groovy/groovewindow.cpp \
    src/groovy/debug.cpp \
    src/groovy/crash.cpp \
    src/groovy/about.cpp \
    src/libgroove_data/song.cpp \
    src/libgroove_data/playlist.cpp \
    src/libgroove_data/artist.cpp \
    src/libgroove_data/album.cpp \
    src/libgroove_data/user.cpp \
    src/libgroove_fetcher/fetcher.cpp \
    src/libgroove_service/request.cpp \
    src/libgroove_service/methods.cpp \
    src/libgroove_service/service.cpp \
    src/libgroove_settings/settings.cpp \
    src/libgroove_songsmodel/songsmodel.cpp \
    src/libgroove_client/client-request.cpp \
    src/libgroove_client/private.cpp \
    src/libgroove_client/client.cpp \
    src/libgroove_playlistmodel/playlistmodel.cpp \
    src/libgroove_searchmodel/searchmodel.cpp
FORMS += src/ui/preferences.ui \
    src/ui/groovewindow.ui \
    src/ui/about.ui
