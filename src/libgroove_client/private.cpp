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

#include "common/make_varmap.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <qjson/parser.h>
#include <qjson/serializer.h>

#include "private.h"

GrooveClient::Private::Private (GrooveClient *parent)
  : QObject (parent)
  , m_networkManager (new QNetworkAccessManager)
{
}

GrooveClient::Private::~Private ()
{
  delete m_networkManager;
}

void
GrooveClient::Private::establishConnection () const
{
  qDebug () << Q_FUNC_INFO << "Making connection";
  QNetworkRequest loginRequest (QUrl ("http://listen.grooveshark.com"));
  QNetworkReply *reply = networkManager ().get (loginRequest);
  connect (reply, SIGNAL (finished ()), SLOT (processPHPSessionId ()));
}

void
GrooveClient::Private::processPHPSessionId ()
{
  qDebug () << Q_FUNC_INFO << "processing";
  QList<QNetworkCookie> cookieList = networkManager ().cookieJar ()->cookiesForUrl (QUrl ("http://listen.grooveshark.com"));

  foreach (const QNetworkCookie &cookie, cookieList)
    if (cookie.name () == "PHPSESSID")
      {
        m_phpCookie = cookie.value ();
        qDebug () << Q_FUNC_INFO << "Got PHP cookie: " << qPrintable (m_phpCookie);
        fetchSessionToken ();
        return;
      }

  /* FIXME */
  GROOVE_VERIFY_OR_DIE (m_phpCookie.length (), "PHP cookie couldn't be set");
}

struct GrooveRequest
{
  explicit GrooveRequest (GrooveClient &client, QString service, QString method = QString ())
    : m_req (QUrl ("https://cowbell.grooveshark.com/" + service))
    , m_client (client)
  {
    m_req.setHeader (m_req.ContentTypeHeader, "application/json");
  }

  void post (QObject *receiver, char const *slot)
  {
    QJson::Serializer serializer;
    QNetworkReply *reply = m_client.networkManager ().post (m_req, serializer.serialize (jlist));
    receiver->connect (reply, SIGNAL (finished ()), slot);
  }

  QNetworkRequest m_req;
  GrooveClient &m_client;
  QVariantMap jlist;
};

static void
operator << (GrooveRequest &request, QVariantOrMap::map const &init)
{
  request.jlist << init;
}

void
GrooveClient::Private::fetchSessionToken ()
{
  qDebug () << Q_FUNC_INFO << "fetching";
  QNetworkRequest tokenRequest (QUrl ("https://cowbell.grooveshark.com/service.php"));
  tokenRequest.setHeader (tokenRequest.ContentTypeHeader, "application/json");

  /* headers and parameters */
  typedef QVariantOrMap::map map;
  QVariantMap jlist;
  jlist << map {
    { "method", "getCommunicationToken" },
    { "header", map {
        { "client", "gslite" },
        { "clientRevision", "20100412.09" },
      },
    },
    { "parameters", map {
        { "secretKey", QCryptographicHash::hash (m_phpCookie.toUtf8 (), QCryptographicHash::Md5).toHex () },
      },
    },
  };

  /* send, hook request */
  QJson::Serializer serializer;
  QNetworkReply *reply = networkManager ().post (tokenRequest, serializer.serialize (jlist));
  connect (reply, SIGNAL (finished ()), SLOT (processSessionToken ()));
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
  GROOVE_VERIFY_OR_DIE (!result["message"].toString ().length (), qPrintable (result["message"].toString ()));

  m_sessionToken = result["result"].toString ();
  qDebug () << Q_FUNC_INFO << "Got session token: " << m_sessionToken;
  emit connected ();
}

const QString &
GrooveClient::Private::sessionToken () const
{
  return m_sessionToken;
}

const QString &
GrooveClient::Private::phpCookie () const
{
  return m_phpCookie;
}

QString
GrooveClient::Private::grooveMessageToken (const QString &method)
{
  if (GROOVE_VERIFY (m_sessionToken.length (), "made a request to create message without session token"))
    return QString ();

  QString rnum = QString (qrand () % 9 + 48)
                 + QString (qrand () % 9 + 48)
                 + QString (qrand () % 9 + 48)
                 + QString (qrand () % 9 + 48)
                 + QString (qrand () % 9 + 48)
                 + QString (qrand () % 9 + 48);

  QString messageToken;
  messageToken.append (method);
  messageToken.append (":");
  messageToken.append (m_sessionToken.toAscii ());
  messageToken.append (":quitStealinMahShit:");
  messageToken.append (rnum);

  QString rs;
  rs.append (rnum);
  rs.append (QCryptographicHash::hash (messageToken.toAscii (), QCryptographicHash::Sha1).toHex ());

  qDebug () << Q_FUNC_INFO << "Produced token " << rs;
  return rs;
}

QNetworkAccessManager &
GrooveClient::Private::networkManager () const
{
  return *m_networkManager;
}
