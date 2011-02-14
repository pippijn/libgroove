TEMPLATE = subdirs
SUBDIRS = libgroove groovy-uic groovy-man groovy-qml

groovy-uic.depends = libgroove
groovy-man.depends = libgroove
groovy-qml.depends = libgroove
