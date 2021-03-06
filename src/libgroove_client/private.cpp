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

#include "client-request.h"

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
  LDEBUG << "Making connection";
  GroovePrivRequest request (*qobject_cast<GrooveClient *> (parent ()), GroovePrivRequest::LOGIN_URL);
  request.get (this, SLOT (processPHPSessionId ()));
}

void
GrooveClient::Private::processPHPSessionId ()
{
  LDEBUG << "processing";
  QList<QNetworkCookie> cookieList = networkManager ().cookieJar ()->cookiesForUrl (QUrl (GroovePrivRequest::LOGIN_URL));

  foreach (QNetworkCookie const &cookie, cookieList)
    if (cookie.name () == "PHPSESSID")
      {
        m_phpCookie = cookie.value ();
        LDEBUG << "Got PHP cookie: " << qPrintable (m_phpCookie);
        fetchSessionToken ();
        return;
      }

  /* FIXME */
  GROOVE_VERIFY_OR_DIE (m_phpCookie.length (), "PHP cookie couldn't be set");
}

void
GrooveClient::Private::fetchSessionToken ()
{
  LDEBUG << "fetching";
  GroovePrivRequest request (*qobject_cast<GrooveClient *> (parent ()), GroovePrivRequest::more ());

  /* headers and parameters */
  typedef QVariantOrMap::map map;
  request << map {
    { "method", "getCommunicationToken" },
    { "header", map {
        { "client", GroovePrivRequest::CLIENT },
        { "clientRevision", GroovePrivRequest::REVISION },
#if 0
        { "country", map {
            { "CC3", "0" },
            { "ID", "55" },
            { "CC1", "18014398509481984" },
            { "IPR", "11409" },
            { "CC4", "0" },
            { "CC2", "0" },
          },
        },
        { "uuid", "31DE93C8-8DE9-4BF8-BA22-289E0CAEC1FD" },
        { "session", m_phpCookie.toUtf8 () },
        { "privacy", 0 },
#endif
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

  QByteArray sessionTokenReply = reply->readAll ();
  QVariantMap result = parser.parse (sessionTokenReply, &ok).toMap ();

  if (!ok)
    LDEBUG << "Session token request failed:" << sessionTokenReply;

  GROOVE_VERIFY_OR_DIE (ok, "couldn't parse reply to session token request");
  GROOVE_VERIFY_OR_DIE (result["message"].toString ().isEmpty (), qPrintable (result["message"].toString ()));

  m_sessionToken = result["result"].toString ();
  LDEBUG << "Got session token: " << m_sessionToken;

  if (!m_sessionToken.length ())
    {
      LDEBUG << "Session token empty:";
      LDEBUG << sessionTokenReply;
      LDEBUG << reply->errorString ();
    }

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

  LDEBUG << "Produced token: " << rs;
  return rs;
}

QNetworkAccessManager &
GrooveClient::Private::networkManager () const
{
  return *m_networkManager;
}
