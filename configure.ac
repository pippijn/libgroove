dnl Copyright © 2010 Pippijn van Steenhoven
dnl See COPYING.AGPL for licence information.
AC_PREREQ(2.61)
AC_INIT([Groovy], [0.1], [groovy@xinutec.org])
AC_CONFIG_AUX_DIR(autoconf)
AC_CONFIG_SRCDIR(autoconf.h.in)
AC_CONFIG_MACRO_DIR(m4/libtool)
AC_CONFIG_HEADERS(autoconf.h)

# automake
LT_INIT
AM_INIT_AUTOMAKE([silent-rules gnits])
AM_SILENT_RULES
AM_DEFAULT_VERBOSITY=0

# build tools
AC_PROG_CXX
AC_PROG_YACC

# pkg-config
AC_PATH_PROG(PKG_CONFIG, pkg-config, no)

# Qt
AC_PKG_CHECK([QtCore], 4.4.0, [QTCORE_])
AC_PKG_CHECK([QtNetwork], 4.4.0, [QTNETWORK_])
AC_PKG_CHECK([QtGui], 4.4.0, [QTGUI_])
AC_PKG_CHECK([QJson], 0.7.1, [QJSON_])
AC_PKG_CHECK([phonon], 4.4.0, [PHONON_])

AC_MSG_CHECKING([moc location])
MOC=`$PKG_CONFIG --variable=moc_location QtCore`
AC_SUBST([MOC])
AC_MSG_RESULT([$MOC])

AC_MSG_CHECKING([uic location])
UIC=`$PKG_CONFIG --variable=uic_location QtCore`
AC_SUBST([UIC])
AC_MSG_RESULT([$UIC])

# debugging
AC_CHECK_HEADERS([dnl
   valgrind/valgrind.h dnl
   valgrind/memcheck.h dnl
   execinfo.h dnl
   bfd.h dnl
])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
