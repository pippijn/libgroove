TEMPLATE = subdirs
SUBDIRS = libgroove groovy-uic groovy-man

groovy-uic.depends = libgroove
groovy-man.depends = libgroove
