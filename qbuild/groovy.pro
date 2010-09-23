TEMPLATE = subdirs
SUBDIRS = libgroove groovy-gen groovy-man

UI_HEADERS_DIR = ../../include/frontend/gen
UI_SOURCES_DIR = ../../src/groovy/frontend/gen

groovy-gen.depends = libgroove
groovy-man.depends = libgroove
