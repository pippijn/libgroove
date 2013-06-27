#include "libgroove_global.h"

#include <QTime>

static struct InitTimer
{
  InitTimer ()
    : begin (0, 0)
  {
    begin.start ();
  }

  QTime begin;
} timer;

static inline QDebug &
operator << (QDebug &dbg, InitTimer const &timer)
{
  return dbg << "["
             << qSetFieldWidth (4)
             << timer.begin.elapsed () / 1000
             << qSetFieldWidth (0)
             << '.'
             << qSetPadChar ('0')
             << qSetFieldWidth (3)
             << timer.begin.elapsed () % 1000
             << qSetFieldWidth (0)
             << qSetPadChar (' ')
             << "] "
             ;
}

QDebug &
log_pre (QDebug &&dbg, char const *file, int line, char const *func)
{
  dbg.nospace () << timer << func << ':';

  return dbg.space ();
}
