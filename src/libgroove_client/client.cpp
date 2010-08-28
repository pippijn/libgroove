/*
 * Copyright (C) 2010 Robin Burchell <robin.burchell@collabora.co.uk>
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

#include <QDebug>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QThreadStorage>

#include "private.h"

GrooveClient::GrooveClient (QObject *parent)
  : QObject (parent)
  , d (new Private (this))
{
  connect (d, SIGNAL (connected ()), this, SIGNAL (connected ()));
}

void
GrooveClient::establishConnection ()
{
  qDebug () << Q_FUNC_INFO << "Making connection";
  QNetworkRequest loginRequest (QUrl ("http://listen.grooveshark.com"));
  QNetworkReply *reply = networkManager ().get (loginRequest);
  connect (reply, SIGNAL (finished ()), d, SLOT (processPHPSessionId ()));
}

QNetworkAccessManager &
GrooveClient::networkManager ()
{
  return d->networkManager ();
}

QString
GrooveClient::phpCookie () const
{
  return d->phpCookie ();
}

QString
GrooveClient::grooveMessageToken (QString const &method) const
{
  return d->grooveMessageToken (method);
}
