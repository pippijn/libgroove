#include "groove/private/make_varmap.h"

#include "groove/client.h"

#include <QNetworkRequest>
#include <QNetworkReply>

#include <qjson/serializer.h>

struct GrooveRequest
{
  GrooveRequest (GrooveRequest const &rhs) = delete;
  GrooveRequest &operator = (GrooveRequest const &rhs) = delete;

  static QString const API_URL;
  static QString const REVISION;

  GrooveRequest (GrooveClient &client, QString service)
    : m_req (QUrl (service))
    , m_client (client)
    , m_jlist ()
  {
  }

  void post (QObject const *receiver, char const *slot)
  {
    m_req.setHeader (m_req.ContentTypeHeader, "application/json");

    QJson::Serializer serializer;
    QNetworkReply *reply = m_client.networkManager ().post (m_req, serializer.serialize (m_jlist));
    receiver->connect (reply, SIGNAL (finished ()), slot);
  }

  QNetworkRequest m_req;
  GrooveClient &m_client;
  QVariantMap m_jlist;
};

static inline QString
more (QString const &method)
{
  return GrooveRequest::API_URL + "more.php?" + method;
}

static inline QString
service (QString const &method)
{
  return GrooveRequest::API_URL + "service.php?" + method;
}

static inline void
operator << (GrooveRequest &request, QVariantOrMap::map const &init)
{
  request.m_jlist << init;
}
