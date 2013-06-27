/*
 * Copyright © 2010 Robin Burchell <robin.burchell@collabora.co.uk>
 * Copyright © 2010 Pippijn van Steenhoven <pippijn@xinutec.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef LIBGROOVE_GLOBAL_H
#define LIBGROOVE_GLOBAL_H

#include <qglobal.h>

#include <QDebug>

#include <boost/implicit_cast.hpp>

using boost::implicit_cast;

#if defined(LIBGROOVE_LIBRARY)
# define LIBGROOVESHARED_EXPORT Q_DECL_EXPORT
#else
# define LIBGROOVESHARED_EXPORT Q_DECL_IMPORT
#endif

LIBGROOVESHARED_EXPORT QDebug &log_pre (QDebug &&dbg, char const *file, int line, char const *func);

#define LOG_PRE(dbg)                    log_pre (dbg, __FILE__, __LINE__, Q_FUNC_INFO)

#define GROOVE_VERIFY(x, y)             (!(x) && ((LOG_PRE (qWarning ()) << y), Q_ASSERT (x), true))
#define GROOVE_VERIFY_OR_DIE(x, y)      if (!(x)) { qFatal ("FATAL: %s: %s", Q_FUNC_INFO, y); }

#define LDEBUG                          LOG_PRE (qDebug ())

#endif /* LIBGROOVE_GLOBAL_H */
