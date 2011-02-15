#define LIVE 1
#include "groove/client.h"
#include "groove/service.h"
#include "groove/searchmodel.h"
#include "groove/playlistmodel.h"

#include "controller.h"

struct Controller::Private
{
  std::shared_ptr<GrooveClient> client;
  std::shared_ptr<GrooveService> service;
  std::shared_ptr<GrooveSearchModel> searchModel;
  std::shared_ptr<GroovePlaylistModel> playlistModel;

  QString lastQuery;

  bool connected;

  Private (QObject *parent)
    : client (new GrooveClient (parent))
    , service (new GrooveService (client, parent))
    , searchModel (new GrooveSearchModel (client, service, parent))
    , playlistModel (new GroovePlaylistModel (client, parent))
    , lastQuery ()
    , connected (false)
  {
  }
};


Controller::Controller (QObject *parent)
  : QObject (parent)
  , self (new Private (this))
{
#if LIVE
  self->client->establishConnection ();
#endif
  connect (self->client.get (), SIGNAL (connected ()), SLOT (connectionEstablished ()));
}

Controller::~Controller ()
{
}


GrooveSearchModel &
Controller::searchModel ()
{
  return *self->searchModel;
}


QString
wsNormed (QString const &s)
{
  return s.trimmed ().replace (QRegExp ("\\s+"), " ");
}

void
Controller::search (QString const &query)
{
  QString nquery = wsNormed (query);
  if (nquery.isEmpty ())
    {
      LDEBUG << "query is empty; not searching";
      return;
    }
  if (nquery == self->lastQuery)
    {
      LDEBUG << "query is unchanged";
      return;
    }
  if (!self->connected)
    {
      LDEBUG << "connecting; not searching";
      return;
    }

  LDEBUG << "search for" << nquery;

  self->lastQuery = nquery;
#if 0
  self->service->getArtistAutocomplete (nquery);
#else
  self->searchModel->searchBySong (nquery);
#endif
}

void
Controller::connectionEstablished ()
{
  self->connected = true;
}
