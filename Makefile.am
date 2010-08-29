AUTOMAKE_OPTIONS	= -Wall -Wno-portability
ACLOCAL_AMFLAGS		= -I m4/libtool -I m4

lib_LTLIBRARIES		= # empty
bin_PROGRAMS		= # empty
pkgdata_DATA		= # empty
include_HEADERS		= # empty
noinst_HEADERS		= # empty

BUILT_SOURCES		= # empty

EXTRA_DIST		= # empty

CLEANFILES		= # empty
DISTCLEANFILES		= # empty
MAINTAINERCLEANFILES	= # empty

OPTFLAGS		= -pipe -O0 -ggdb3
WARNINGS		= # empty
#WARNINGS		+= -Wall -Wextra
#WARNINGS		+= -Wno-unused-parameter
#WARNINGS		+= -Wpadded
#WARNINGS		+= -Wpacked
#WARNINGS		+= -Wconversion
#WARNINGS		+= -Wstrict-overflow=5
#WARNINGS		+= -Wstrict-aliasing=1
#WARNINGS		+= -Werror

AM_CFLAGS		= $(OPTFLAGS) $(WARNINGS)
AM_CXXFLAGS		= $(OPTFLAGS) $(WARNINGS) -std=c++0x
AM_CPPFLAGS		= -I$(srcdir)/include -fvisibility=hidden
AM_LDFLAGS		= -Wl,-z,defs

AM_CPPFLAGS		+= -DPKGDATADIR='"$(pkgdatadir)"'

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

clean-local:
	$(RM) -r include src ui_*.h

run: groovy
	./$<

package: all
	$(RM) -r $(PACKAGE_TARNAME)-$(PACKAGE_VERSION)
	$(MAKE) install DESTDIR=$(PWD)/$(PACKAGE_TARNAME)-$(PACKAGE_VERSION)
	tar zcf $(PACKAGE_TARNAME)-$(PACKAGE_VERSION)_$(host_cpu).tar.gz $(PACKAGE_TARNAME)-$(PACKAGE_VERSION)
