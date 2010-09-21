/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

#include "groove/private/make_varmap.h"
class GrooveClient;

#include <QVariant>

#include <memory>

class LIBGROOVESHARED_EXPORT GrooveService
  : public QObject
{
  Q_OBJECT

private: // types
  typedef QVariantOrMap::pair pair;
  typedef QVariantOrMap::map map;
  typedef QVariantOrMap::array array;

private: // functions
  pair country () const;
  map header (char const *method) const;

public: // ctor/dtor
  GrooveService (std::shared_ptr<GrooveClient> client, QObject *parent);
  ~GrooveService ();

public: // functions
  void addSongsToQueueExt (uint songQueueID, map songQueueSongIDs);
  void artistGetFans (uint offset, uint artistID);
  void artistGetSimilarArtists (uint artistID);
  void artistGetSongs (uint offset, uint artistID, bool isVerified);
  void authenticateUserEx (QString password, QString username);
  void autoplayGetSong (array frowns);
  void autoplayRemoveVoteDownEx ();
  void autoplayRemoveVoteUpEx ();
  void autoplayVoteDownEx ();
  void autoplayVoteUpEx ();
  void broadcastSong ();
  void createWidgetIDFromSongIDs ();
  void deletePlaylist ();
  void favorite ();
  void forgotPassword ();
  void getAffiliateDownloadURLs ();
  void getArtistAutocomplete ();
  void getArtistByID ();
  void getArtistsForTag ();
  void getAutoCoolPlaylistName ();
  void getCombinedFeedData ();
  void getCommunicationToken ();
  void getContactInfoForFollowedUsers ();
  void getCountryFromRequestIP ();
  void getDetailsForBroadcast ();
  void getEmailAddress ();
  void getFavouriteIDs ();
  void getFavourites ();
  void getPlaylistByID ();
  void getQueueSongListFromSongIDs ();
  void getRecentlyActiveUsers ();
  void getSearchResults (QString searchTerm, QString type);
  void getSimilarUsers ();
  void getSongForAutoplayExt ();
  void getStationByID ();
  void getStreamKeyFromSongID ();
  void getStreamKeyFromSongIdEx (bool mobile, bool prefetch, uint songID);
  void getTokenForSong ();
  void getUserByID ();
  void getUserSettings ();
  void getUserSidebar ();
  void initiateQueueEx ();
  void logoutUser ();
  void logTargetedThemeImpression ();
  void markSongAsDownloaded ();
  void markSongComplete ();
  void markSongQueueSongPlayed ();
  void markSongSkipped ();
  void markStreamKeyOver30Seconds ();
  void overwriteExistingPlaylist ();
  void playlistGetFans ();
  void popularGetSongs ();
  void registerUserEx ();
  void removeSongsFromQueueExte ();
  void renamePlaylist ();
  void reportBroadcast ();
  void setPlaylistAbout ();
  void unFavorite ();
  void updateLastfmService ();
  void updateStreamKeyLength ();
  void userAddSongToLibrary ();
  void userGetFans ();
  void userGetLibraryTSModified ();
  void userGetPlaylists ();
  void userGetSongsInLibrary ();

private: // data
  std::shared_ptr<GrooveClient> m_client;
};
