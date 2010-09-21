ACLOCAL_AMFLAGS		= -I m4/libtool -I m4

include src/common.am

OPTFLAGS		= -pipe -O3 -ggdb3 -fno-inline
WARNINGS		= # empty
WARNINGS		+= -isystem /usr/include/qt4/QtCore
WARNINGS		+= -isystem /usr/include/qt4/QtGui
WARNINGS		+= -isystem /usr/include/qt4
WARNINGS		+= -isystem .
WARNINGS		+= -Wall -Wextra
WARNINGS		+= -Wno-unused-parameter
#WARNINGS		+= -Wpadded -Wno-error=padded
#WARNINGS		+= -Wpacked
WARNINGS		+= -Wconversion
WARNINGS		+= -Weffc++
WARNINGS		+= -Wstrict-overflow=4
WARNINGS		+= -Wstrict-aliasing=3
#WARNINGS		+= -Werror

AM_CFLAGS		= $(OPTFLAGS) $(WARNINGS)
AM_CXXFLAGS		= $(OPTFLAGS) $(WARNINGS) -std=c++0x

include include/Rules.am
include res/Rules.am
include src/Rules.am

-include prepare
prepare:	

%.moc.cpp: %.h
	$(MKDIR_P) `dirname $@`
	$(MOC) -I$(srcdir)/include $< -o $@

VPATH += $(srcdir)/src/ui

ui_%.h: %.ui
	$(UIC) $< -o $@

run: all
	./groovy

valgrind: all
	valgrind				\
		--track-origins=yes		\
		--num-callers=40		\
		--leak-check=full		\
		--gen-suppressions=yes		\
		--suppressions=../suppressions	\
		.libs/groovy
