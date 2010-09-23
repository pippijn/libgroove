TEMPLATE = subdirs
SUBDIRS = libgroove groovy-gen groovy-man

groovy-gen.depends = libgroove
groovy-man.depends = libgroove

