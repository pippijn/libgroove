/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "request.h"

#include "groove/client.h"
#include "groove/service.h"

#include <qjson/parser.h>

#include <QUuid>

GrooveService::GrooveService (std::shared_ptr<GrooveClient> client, char const *slot, QObject *parent)
  : QObject (parent)
  , m_client (client)
  , m_slot (slot)
{
}

GrooveService::~GrooveService ()
{
}

GrooveService::pair
GrooveService::country () const
{
  return
    { "country", map {
        { "CC1", "0" },
        { "CC3", "0" },
        { "ID", "223" },
        { "CC2", "0" },
        { "CC4", "1073741824" },
      },
    };
}

GrooveService::map
GrooveService::header (char const *method) const
{
#if 0
  QString uuid = QUuid::createUuid ().toString ().toUpper ().mid (1, 36);
  LDEBUG << uuid;
#endif
  return map {
    { "method", method },
    { "header", map {
        { "session", m_client->phpCookie ().toUtf8 () },
        { "token", m_client->grooveMessageToken (method) },
        { "client", "gslite" },
        { "clientRevision", GrooveRequest::REVISION },
#if 0
        { "privacy", 0 },
        { "uuid", uuid },
#endif
        country (),
      },
    },
  };
}


QVariantMap
GrooveService::getReply () const
{
  QNetworkReply *reply = qobject_cast<QNetworkReply *> (sender ());
  if (GROOVE_VERIFY (reply, "reply without a QNetworkReply"))
    return { };

  QByteArray response = reply->readAll ();
  LDEBUG << "response: " << response;

  QJson::Parser parser;
  bool ok;
  QVariantMap result = parser.parse (response, &ok).toMap ();
  if (GROOVE_VERIFY (ok, "error occured whilst parsing reply"))
    return { };

  return result;
}
