#include <iostream>
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

#include "private.h"

#include "groove/private/request.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkCookieJar>

#include <qjson/parser.h>

GrooveClient::Private::Private (GrooveClient *parent)
  : QObject (parent)
  , m_phpCookie ()
  , m_sessionToken ()
  , m_networkManager (new QNetworkAccessManager)
{
}

GrooveClient::Private::~Private ()
{
}

void
GrooveClient::Private::establishConnection () const
{
  llog << DEBUG << LOG_FUNC << "Making connection";
  GrooveRequest request (*qobject_cast<GrooveClient *> (parent ()), GrooveRequest::LOGIN_URL);
  request.get (this, SLOT (processPHPSessionId ()));
}

void
GrooveClient::Private::processPHPSessionId ()
{
  llog << DEBUG << LOG_FUNC << "processing";
  QList<QNetworkCookie> cookieList = networkManager ().cookieJar ()->cookiesForUrl (QUrl (GrooveRequest::LOGIN_URL));

  foreach (QNetworkCookie const &cookie, cookieList)
    if (cookie.name () == "PHPSESSID")
      {
        m_phpCookie = cookie.value ();
        llog << DEBUG << LOG_FUNC << "Got PHP cookie: " << qPrintable (m_phpCookie);
        fetchSessionToken ();
        return;
      }

  /* FIXME */
  GROOVE_VERIFY_OR_DIE (m_phpCookie.length (), "PHP cookie couldn't be set");
}

void
GrooveClient::Private::fetchSessionToken ()
{
  llog << DEBUG << LOG_FUNC << "fetching";
  GrooveRequest request (*qobject_cast<GrooveClient *> (parent ()), GrooveRequest::service ());

  /* headers and parameters */
  typedef QVariantOrMap::map map;
  request << map {
    { "method", "getCommunicationToken" },
    { "header", map {
        { "client", "gslite" },
        { "clientRevision", GrooveRequest::REVISION },
      },
    },
    { "parameters", map {
        { "secretKey", QCryptographicHash::hash (m_phpCookie.toUtf8 (), QCryptographicHash::Md5).toHex () },
      },
    },
  };

  /* send, hook request */
  request.post (this, SLOT (processSessionToken ()));
}

void
GrooveClient::Private::processSessionToken ()
{
  QNetworkReply *reply = qobject_cast<QNetworkReply *> (sender ());

  if (GROOVE_VERIFY (reply, "called without a QNetworkReply as sender"))
    return;

  bool ok;
  QJson::Parser parser;
  QVariantMap result = parser.parse (reply->readAll (), &ok).toMap ();

  /* TODO */
  GROOVE_VERIFY_OR_DIE (ok, "couldn't parse reply to session token request");
  GROOVE_VERIFY_OR_DIE (result["message"].toString ().isEmpty (), qPrintable (result["message"].toString ()));

  m_sessionToken = result["result"].toString ();
  llog << DEBUG << LOG_FUNC << "Got session token: " << m_sessionToken;
  emit connected ();
}

QString const &
GrooveClient::Private::sessionToken () const
{
  return m_sessionToken;
}

QString const &
GrooveClient::Private::phpCookie () const
{
  return m_phpCookie;
}

QString
GrooveClient::Private::grooveMessageToken (QString const &method) const
{
  if (GROOVE_VERIFY (m_sessionToken.length (), "made a request to create message without session token"))
    return QString ();

  QString rnum = QString (qrand () % 9 + 48)
               + QString (qrand () % 9 + 48)
               + QString (qrand () % 9 + 48)
               + QString (qrand () % 9 + 48)
               + QString (qrand () % 9 + 48)
               + QString (qrand () % 9 + 48)
               ;

  QString messageToken;
  messageToken.append (method);
  messageToken.append (":");
  messageToken.append (m_sessionToken.toAscii ());
  messageToken.append (":quitStealinMahShit:");
  messageToken.append (rnum);

  QString rs;
  rs.append (rnum);
  rs.append (QCryptographicHash::hash (messageToken.toAscii (), QCryptographicHash::Sha1).toHex ());

  llog << DEBUG << LOG_FUNC << "Produced token: " << rs;
  return rs;
}

QNetworkAccessManager &
GrooveClient::Private::networkManager () const
{
  return *m_networkManager;
}
