#define LIVE            1
#define LIVE_SEARCH     0
#define LIVE_COMPLETION 1
#include <QStringList>

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

  QString lastAutocompleteQuery;
  QString lastSearchQuery;

  bool connected;

  Private (QObject *parent)
    : client (new GrooveClient (parent))
    , service (new GrooveService (client, parent))
    , searchModel (new GrooveSearchModel (client, service, parent))
    , playlistModel (new GroovePlaylistModel (client, parent))
    , lastAutocompleteQuery ()
    , lastSearchQuery ()
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
  if (nquery == self->lastSearchQuery)
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

  self->lastSearchQuery = nquery;
#if LIVE_SEARCH
  self->searchModel->searchBySong (nquery);
#endif
}

void
Controller::autocomplete (QString const &query)
{
  QString nquery = wsNormed (query);
  if (nquery.isEmpty ())
    {
      LDEBUG << "query is empty; not searching";
      return;
    }
  if (nquery == self->lastAutocompleteQuery)
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

  self->lastAutocompleteQuery = nquery;
#if LIVE_COMPLETION
  connect ( self->service.get ()
          , SIGNAL (getArtistAutocomplete_success (QStringList const &))
          , this
          , SLOT (updateCompletion (QStringList const &)));
  self->service->getArtistAutocomplete (nquery);
#endif
}

void
Controller::connectionEstablished ()
{
  self->connected = true;
}
