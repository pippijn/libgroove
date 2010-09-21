/*
 * This file is part of libgroove
 *
 * Copyright © 2010 Robin Burchell <robin.burchell@collabora.co.uk>
 *
 * This software, including documentation, is protected by copyright.
 * All rights are reserved.
 *
 * Copying, including reproducing, storing, adapting or translating, any or
 * all of this material requires prior written consent of the author.
 *
 * This material may also contain confidential information which may not be
 * disclosed to others without the prior written consent of the author.
 */

#ifndef LIBGROOVE_GLOBAL_H
#define LIBGROOVE_GLOBAL_H

#include <log4cpp/Category.hh>
#include <QtCore/qglobal.h>

#include <QString>
#include <QByteArray>

namespace
{
  static __attribute__ ((__unused__)) log4cpp::Category &llog = log4cpp::Category::getRoot ();

  static __attribute__ ((__unused__)) auto const FATAL = log4cpp::Priority::FATAL;
  static __attribute__ ((__unused__)) auto const WARN = log4cpp::Priority::WARN;
  static __attribute__ ((__unused__)) auto const DEBUG = log4cpp::Priority::DEBUG;
}

#if defined(LIBGROOVE_LIBRARY)
# define LIBGROOVESHARED_EXPORT Q_DECL_EXPORT
#else
# define LIBGROOVESHARED_EXPORT Q_DECL_IMPORT
#endif

#define LOG_FUNC Q_FUNC_INFO << ": "

#define GROOVE_VERIFY(x, y) (!(x) && ((llog << WARN << LOG_FUNC << y), Q_ASSERT (x), true))
#define GROOVE_VERIFY_OR_DIE(x, y) if (!(x)) { llog << FATAL << LOG_FUNC << y; }

static inline std::ostream &
operator << (std::ostream &cs, QByteArray const &b)
{
  return cs << b.data ();
}

static inline std::ostream &
operator << (std::ostream &cs, QString const &s)
{
  return cs << s.toUtf8 ();
}

#endif /* LIBGROOVE_GLOBAL_H */
