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

#ifndef GROOVECLIENT_P_H
#define GROOVECLIENT_P_H

#include "groove/client.h"

#include <QObject>
#include <QString>
#include <QNetworkAccessManager>

#include <memory>

class GrooveClient::Private
  : public QObject
{
  Q_OBJECT

public:
  explicit Private (GrooveClient *parent);
  ~Private ();

  void establishConnection () const;

  QString const &phpCookie () const;
  QString const &sessionToken () const;

  QString grooveMessageToken (QString const &method) const;
  QNetworkAccessManager &networkManager () const;

signals:
  /*!
   *  Indicates that the client made a session with Grooveshark successfully.
   */
  void connected ();

private slots:
  /*!
   *  Processes the first stage of the Grooveshark login process.
   */
  void processPHPSessionId ();

  /*!
   *  Process the second stage of the Grooveshark login process.
   */
  void processSessionToken ();

  /*!
   *  Fetch a token to communicate with Grooveshark with.
   *
   *  You should generally not need to call this in user code, use login() directly.
   */
  void fetchSessionToken ();

private:
  QString m_phpCookie;
  QString m_sessionToken;
  std::auto_ptr<QNetworkAccessManager> m_networkManager;
};

#endif /* GROOVECLIENT_P_H */
