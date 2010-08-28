AC_DEFUN([AC_PKG_CHECK],[
   AC_MSG_CHECKING($1 >= $2)
   if $PKG_CONFIG $1 --atleast-version $2; then
      CXXFLAGS="$CXXFLAGS `$PKG_CONFIG $1 --cflags`"
      LIBS="$LIBS `$PKG_CONFIG $1 --libs`"
      AC_MSG_RESULT(ok)
   else
      AC_MSG_ERROR(no)
   fi
])
