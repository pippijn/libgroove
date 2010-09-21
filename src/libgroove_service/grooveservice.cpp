/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "request.h"

#include "groove/service.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QVariantMap>

#include <qjson/parser.h>

GrooveService::GrooveService (std::shared_ptr<GrooveClient> client, QObject *parent)
  : m_client (client)
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
  return map {
    { "method", method },
    { "header", map {
        { "session", m_client->phpCookie ().toUtf8 () },
        { "token", m_client->grooveMessageToken (method) },
        { "client", "gslite" },
        { "clientRevision", GrooveRequest::REVISION },
        country (),
      },
    },
  };
}

/**
 * This method adds songs to the queue of songs to be played.
 *
 * Parameters:
 * \param songQueueID: unknown, integer number specifying the queue to add to
 * \param songIDsArtistIDs: an array of objects, specified below which determine which songs to add to the queue
 *
 * \c artistID: the artist ID of the song
 * \c songQueueSongID: the position of the song in the queue (integer, starting at 1)
 * \c source: the source of this request, usually set to string "user" but may be set to "sponsored" when
 *            using Grooveshark Radio.
 * \c songID: the song ID
 */
void
GrooveService::addSongsToQueueExt (uint songQueueID, map songQueueSongIDs)
{
  static char const *method = __func__;

  GrooveRequest request (*m_client, service (method));

  request << header (method);
  request << map {
    { "parameters", map {
        { "songQueueID", songQueueID },
        { "songQueueSongIDs", songQueueSongIDs },
      },
    },
  };

  request.post (this, SLOT (searchCompleted ()));
}


/**
 * This method searches for a song using a provided search term
 *
 * Parameters:
 * \param query: the search query
 * \param type: the search type (types are 'Songs', 'Artists', 'Albums' or 'Playlists')
 */
void
GrooveService::getSearchResults (QString query, QString type)
{
  static char const *method = __func__;

  GrooveRequest request (*m_client, more (method));

  request << header (method);
  request << map {
    { "parameters", map {
        { "type", type },
        { "query", query },
      },
    },
  };

  request.post (this, SLOT (searchCompleted ()));
}

/**
 * This method gets the streamKey needed to request the download link to the MP3.
 *
 * Parameters:
 * \param mobile: whether you are using a mobile client or desktop client (true/false).
 *                official client sets this to false but will still work if omitted entirely.
 *                Unknown if a different quality MP3 is retrieved or not.
 * \param prefetch: whether or not the song is being pre-fetched (i.e. downloaded before needed).
 *                  usually safe to set this to false
 * \param songID: the songID of the song you want to download.
 */
void
GrooveService::getStreamKeyFromSongIdEx (bool mobile, bool prefetch, uint songID)
{
  static char const *method = __func__;

  GrooveRequest request (*m_client, more (method));

  request << header (method);
  request << map {
    { "parameters", map {
        country (),
        { "mobile", mobile },
        { "prefetch", prefetch },
        { "songID", songID },
      },
    },
  };

  request.post (this, SLOT (searchCompleted ()));
}
