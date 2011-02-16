/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#define LIVE            1
#define LIVE_SEARCH     1
#define LIVE_COMPLETION 0
#include <QStringList>

#include "groove/client.h"
#include "groove/controller.h"
#include "groove/playlistmodel.h"
#include "groove/searchmodel.h"
#include "groove/service.h"

struct GrooveController::Private
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


GrooveController::GrooveController (QObject *parent)
  : QObject (parent)
  , self (new Private (this))
{
#if LIVE
  self->client->establishConnection ();
#endif
  connect (self->client.get (), SIGNAL (connected ()), SLOT (connectionEstablished ()));
}

GrooveController::~GrooveController ()
{
}


GroovePlaylistModel &
GrooveController::playlistModel ()
{
  return *self->playlistModel;
}

GrooveSearchModel &
GrooveController::searchModel ()
{
  return *self->searchModel;
}


static QString
wsNormed (QString const &s)
{
  return s.trimmed ().replace (QRegExp ("\\s+"), " ");
}

void
GrooveController::search (QString const &query)
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
GrooveController::play (int index)
{
  LDEBUG << "playing" << index;
}

void
GrooveController::enqueue (int index)
{
  LDEBUG << "enqueueing" << index;
  self->playlistModel->append (self->searchModel->songByIndex (index));
}

void
GrooveController::unqueue (int index)
{
  LDEBUG << "unqueueing" << index;
  self->playlistModel->removeAt (index);
}

void
GrooveController::autocomplete (QString const &query)
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
GrooveController::connectionEstablished ()
{
  self->connected = true;
}
