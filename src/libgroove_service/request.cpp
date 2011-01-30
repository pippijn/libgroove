#include "request.h"

QString const GrooveRequest::API_URL      = "https://listen.grooveshark.com/";
QString const GrooveRequest::ART_BASE_URL = "http://beta.grooveshark.com/static/amazonart/m";
QString const GrooveRequest::LOGIN_URL    = "http://listen.grooveshark.com/";
QString const GrooveRequest::CLIENT       = "htmlshark";
QString const GrooveRequest::REVISION     = "20101012.37";

GrooveRequest::pair
GrooveRequest::country ()
{
  return
    { "country", map {
        { "CC1", "18014398509481984" },
        { "CC2", "0" },
        { "CC3", "0" },
        { "CC4", "0" },
        { "ID", "55" },
        { "IPR", "10198" },
      },
    };
}

GrooveRequest::map
GrooveRequest::header (char const *method, char const *clientname) const
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
        { "client", clientname },
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
