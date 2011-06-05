%init ("-Wno-portability")

AM_CPPFLAGS		+= -I$(srcdir)/include -fvisibility=hidden
AM_CPPFLAGS		+= -DPKGDATADIR='"$(pkgdatadir)"'

OPTFLAGS		= -pipe -O3 -ggdb3 -fno-inline
WARNINGS		= # empty
%nowarn-qt ("WARNINGS")
WARNINGS		+= -Wall -Wextra -pedantic
WARNINGS		+= -Wno-unused-parameter
#WARNINGS		+= -Wpadded -Wno-error=padded
#WARNINGS		+= -Wpacked
WARNINGS		+= -Wconversion
WARNINGS		+= -Weffc++
WARNINGS		+= -Wstrict-overflow=4
WARNINGS		+= -Wstrict-aliasing=3
#WARNINGS		+= -Werror

AM_CXXFLAGS		+= $(OPTFLAGS) $(WARNINGS) -std=c++0x -DLIBGROOVE_LIBRARY

# QtCore
AM_CXXFLAGS		+= $(QTCORE_CXXFLAGS)
AM_LDFLAGS		+= $(QTCORE_LIBS)

include include/Rules.am
include qbuild/Rules.am
include res/Rules.am
include src/Rules.am

%.moc.cpp: %.h
	@$(MKDIR_P) $(@D)
	$(AM_V_GEN)$(MOC) -I$(srcdir)/include $< -o $@

run: all
	./groovy-uic

valgrind: all
	libtool --mode=execute			\
	valgrind				\
		--track-origins=yes		\
		--num-callers=40		\
		--leak-check=full		\
		--gen-suppressions=yes		\
		--suppressions=../suppressions	\
		$(builddir)/groovy
