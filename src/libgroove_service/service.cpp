/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "reply.h"
#include "request.h"

#include "groove/client.h"
#include "groove/service.h"

#include <qjson/parser.h>

#include <QUuid>

GrooveService::GrooveService (std::shared_ptr<GrooveClient> client, QObject *parent)
  : QObject (parent)
  , m_client (client)
{
}

GrooveService::~GrooveService ()
{
}


GrooveReply
GrooveService::getReply () const
{
  QNetworkReply *reply = qobject_cast<QNetworkReply *> (sender ());
  if (GROOVE_VERIFY (reply, "reply without a QNetworkReply"))
    return { };

  QByteArray response = reply->readAll ();
#if 0
  LDEBUG << "response: " << response;
#endif

  QJson::Parser parser;
  bool ok;
  QVariant result = parser.parse (response, &ok);
  if (GROOVE_VERIFY (ok, "error occured whilst parsing reply"))
    return { };

  return result;
}

GrooveReply
GrooveService::getResult () const
{
  return getReply ()["result"];
}
