#include "groove/private/make_varmap.h"

#include "groove/client.h"

#include <QNetworkRequest>
#include <QNetworkReply>

#include <qjson/serializer.h>

struct GrooveRequest
{
private: // types
  typedef QVariantOrMap::pair pair;
  typedef QVariantOrMap::map map;
  typedef QVariantOrMap::array array;

public:
  GrooveRequest (GrooveRequest const &rhs) = delete;
  GrooveRequest &operator = (GrooveRequest const &rhs) = delete;

  static QString const API_URL;
  static QString const ART_BASE_URL;
  static QString const LOGIN_URL;
  static QString const CLIENT;
  static QString const REVISION;

  GrooveRequest (std::shared_ptr<GrooveClient> client, QString service (QString const &), char const *method, char const *clientname = "htmlshark")
    : m_req (QUrl (service (method)))
    , m_client (client)
    , m_jlist ()
  {
    m_jlist << header (method, clientname);
  }

  struct parameter_adder;

  parameter_adder parameters ();

  void post (QObject const *receiver, char const *slot)
  {
    m_req.setHeader (m_req.ContentTypeHeader, "application/json");

    QJson::Serializer serializer;
    QByteArray request = serializer.serialize (m_jlist);
    LDEBUG << "request:" << request;
    QNetworkReply *reply = m_client->networkManager ().post (m_req, request);
    receiver->connect (reply, SIGNAL (finished ()), slot);
  }

  static pair country ();
  map header (char const *method, char const *clientname) const;

  QNetworkRequest m_req;
  std::shared_ptr<GrooveClient> m_client;
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


struct GrooveRequest::parameter_adder
{
  typedef QVariantOrMap::map map;

  parameter_adder (parameter_adder const &rhs) = delete;
  parameter_adder &operator = (parameter_adder const &rhs) = delete;

  parameter_adder (GrooveRequest &request)
    : m_request (request)
    , m_map ()
    , m_key ("parameters")
  {
  }

  parameter_adder (parameter_adder &&rhs)
    : m_request (rhs.m_request)
    , m_map (rhs.m_map)
    , m_key (rhs.m_key)
  {
    rhs.m_key = NULL;
  }

  ~parameter_adder ()
  {
    if (m_key)
      m_request << map {
        { m_key, m_map },
      };
  }

  void operator << (QVariantOrMap &&init)
  {
    GROOVE_VERIFY_OR_DIE (m_map.empty (), "attempted to add multiple parameter sets");
#if 0
    if (init.isMap ())
      init.map_value.push_back (country ());
#endif
    m_map = init;
  }

  GrooveRequest &m_request;
  QVariantOrMap m_map;
  char const *m_key;
};

inline GrooveRequest::parameter_adder
GrooveRequest::parameters ()
{
  return parameter_adder (*this);
}
