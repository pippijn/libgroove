#define WITH_UUID 0
#if WITH_UUID
#include <QUuid>
#endif

#include "request.h"

QString const GrooveRequest::API_URL      = "https://listen.grooveshark.com/";
QString const GrooveRequest::ART_BASE_URL = "http://beta.grooveshark.com/static/amazonart/m";
QString const GrooveRequest::LOGIN_URL    = "http://listen.grooveshark.com/";
QString const GrooveRequest::CLIENT       = "htmlshark";
QString const GrooveRequest::REVISION     = "20101222";

GrooveRequest::pair
GrooveRequest::country ()
{
  return
    { "country", map {
        { "ID", "55" },
        { "CC1", "18014398509481984" },
        { "CC2", "0" },
        { "CC3", "0" },
        { "CC4", "0" },
        { "IPR", "9073" },
      },
    };
}

GrooveRequest::map
GrooveRequest::header (char const *method, char const *clientname) const
{
#if WITH_UUID
  static QString uuid = QUuid::createUuid ().toString ().toUpper ().mid (1, 36);
  LDEBUG << uuid;
#endif
  return map {
    { "method", method },
    { "header", map {
        { "session", m_client->phpCookie ().toUtf8 () },
        { "token", m_client->grooveMessageToken (method) },
        { "client", clientname },
        { "clientRevision", GrooveRequest::REVISION },
#if 0
        { "privacy", 0 },
#endif
#if WITH_UUID
        { "uuid", uuid },
#endif
        country (),
      },
    },
  };
}
