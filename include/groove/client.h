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

#ifndef GROOVECLIENT_H
#define GROOVECLIENT_H

#include "libgroove_global.h"

#include <QObject>
class QNetworkAccessManager;

class LIBGROOVESHARED_EXPORT GrooveClient
  : public QObject
{
  Q_OBJECT

public:
  GrooveClient (QObject *parent);
  ~GrooveClient ();

public slots:
  /*!
   *  Initialises the connection to Grooveshark.
   */
  void establishConnection ();

  QNetworkAccessManager &networkManager ();
  QString phpCookie () const;
  QString grooveMessageToken (QString const &method) const;

signals:
  /*!
   *  Indicates that the client made a session with Grooveshark successfully.
   */
  void connected ();

private:
  class Private;
  Private *d;
};

#endif /* GROOVECLIENT_H */
