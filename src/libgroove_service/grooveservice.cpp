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
GrooveService::addSongsToQueueExt (uint songQueueID, map songIDsArtistIDs)
{
  static char const *method = __func__;

  GrooveRequest request (*m_client, service (method));

  request << header (method);
  request << map {
    { "parameters", map {
        { "songQueueID", songQueueID },
        { "songIDsArtistIDs", songIDsArtistIDs },
      },
    },
  };

  request.post (this, SLOT (searchCompleted ()));
}

void
GrooveService::artistGetFans (uint offset, uint artistID)
{
}

void
GrooveService::artistGetSimilarArtists (uint artistID)
{
}

void
GrooveService::artistGetSongs (uint offset, uint artistID, bool isVerified)
{
}

void
GrooveService::authenticateUserEx (QString password, QString username)
{
}

void
GrooveService::autoplayGetSong ()
{
}

void
GrooveService::autoplayRemoveVoteDownEx (uint songQueueID, uint songQueueSongID)
{
}

void
GrooveService::autoplayRemoveVoteUpEx (uint songQueueID, uint songQueueSongID)
{
}

void
GrooveService::autoplayVoteDownEx (uint songQueueID, uint songQueueSongID)
{
}

void
GrooveService::autoplayVoteUpEx (uint songQueueID, uint songQueueSongID)
{
}

void
GrooveService::broadcastSong (QString message, QString link, QString username, QString password, uint songID, QString service, bool saveCredentials)
{
}

void
GrooveService::createWidgetIDFromSongIDs (QList<uint> songIDs)
{
}

void
GrooveService::deletePlaylist (uint playlistID)
{
}

void
GrooveService::favorite (uint id, QString what)
{
}

void
GrooveService::forgotPassword (void)
{
}

void
GrooveService::getAffiliateDownloadURLs (QString songName, QString artistName)
{
}

void
GrooveService::getArtistAutocomplete ()
{
}

void
GrooveService::getArtistByID (uint artistID)
{
}

void
GrooveService::getArtistsForTag (TagID tagID)
{
}

void
GrooveService::getAutoCoolPlaylistName ()
{
}

void
GrooveService::getCombinedFeedData (uint loggedInUserID, QDate day, QList<uint> userIDs)
{
}

void
GrooveService::getCommunicationToken ()
{
}

void
GrooveService::getContactInfoForFollowedUsers ()
{
}

void
GrooveService::getCountryFromRequestIP ()
{
}

void
GrooveService::getDetailsForBroadcast (uint songID)
{
}

void
GrooveService::getEmailAddress ()
{
}

void
GrooveService::getFavouriteIDs (uint userID, QString ofWhat)
{
}

void
GrooveService::getFavourites (uint userID, QString ofWhat)
{
}

void
GrooveService::getPlaylistByID ()
{
}

void
GrooveService::getQueueSongListFromSongIDs (QList<uint> songIDs)
{
}

void
GrooveService::getRecentlyActiveUsers ()
{
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

void
GrooveService::getSimilarUsers ()
{
}

void
GrooveService::getSongForAutoplayExt ()
{
}

void
GrooveService::getStationByID ()
{
}

void
GrooveService::getStreamKeyFromSongID (bool mobile, bool prefetch, uint songID)
{
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
GrooveService::getStreamKeyFromSongIDEx (bool mobile, bool prefetch, uint songID)
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

void
GrooveService::getTokenForSong (uint songID)
{
}

void
GrooveService::getUserByID ()
{
}

void
GrooveService::getUserSettings ()
{
}

void
GrooveService::getUserSidebar ()
{
}

void
GrooveService::initiateQueueEx ()
{
}

void
GrooveService::logoutUser ()
{
}

void
GrooveService::logTargetedThemeImpression ()
{
}

void
GrooveService::markSongAsDownloaded (uint streamServerID, QString streamKey, uint songID)
{
}

void
GrooveService::markSongComplete (uint streamServerID, QString streamKey, uint songID)
{
}

void
GrooveService::markSongQueueSongPlayed (uint songQueueID, uint songQueueSongID, uint streamServerID, QString streamKey, uint songID)
{
}

void
GrooveService::markSongSkipped (uint songQueueID, uint songQueueSongID)
{
}

void
GrooveService::markStreamKeyOver30Seconds (uint songQueueID, uint songQueueSongID, uint streamServerID, QString streamKey, uint songID)
{
}

void
GrooveService::overwriteExistingPlaylist (uint playlistID, QList<uint> songIDs)
{
}

void
GrooveService::playlistGetFans (uint playlistID)
{
}

void
GrooveService::popularGetSongs (QString type)
{
}

void
GrooveService::registerUserEx ()
{
}

void
GrooveService::removeSongsFromQueueExte (bool userRemoved, QList<uint> songQueueSongIDs, uint songQueueID)
{
}

void
GrooveService::renamePlaylist (uint playlistID, QString playlistName)
{
}

void
GrooveService::reportBroadcast ()
{
}

void
GrooveService::setPlaylistAbout (uint playlistID, QString about)
{
}

void
GrooveService::unFavorite (uint id, QString what)
{
}

void
GrooveService::updateLastfmService (QString token, int flagsRemove, QString username, QString session, int flagsAdd)
{
}

void
GrooveService::updateStreamKeyLength (uint streamServerID, uint songID, QString streamKey, float length)
{
}

void
GrooveService::userAddSongToLibrary ()
{
}

void
GrooveService::userGetFans ()
{
}

void
GrooveService::userGetLibraryTSModified ()
{
}

void
GrooveService::userGetPlaylists (uint userID)
{
}

void
GrooveService::userGetSongsInLibrary (QString page, uint userID)
{
}
