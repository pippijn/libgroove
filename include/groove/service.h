/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

#include "groove/private/make_varmap.h"
class GrooveClient;

#include <QDate>
#include <QVariant>

#include <memory>

enum class TagID
{
  Rap = 3,
  RnB = 4,
  Rock = 12,
  Alternative = 13,
  Metal = 17,
  HipHop = 29,
  Jazz = 43,
  Pop = 56,
  Electronica = 67,
  Trance = 69,
  Ambient = 75,
  Country = 80,
  Bluegrass = 96,
  Oldies = 102,
  Punk = 111,
  Folk = 122,
  Indie = 136,
  Reggae = 160,
  Experimental = 191,
  Blues = 230,
  Latin = 528,
  Classical = 750,
  ClassicRock = 3529,
};

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
  void autoplayGetSong ();
  void autoplayRemoveVoteDownEx (uint songQueueID, uint songQueueSongID);
  void autoplayRemoveVoteUpEx (uint songQueueID, uint songQueueSongID);
  void autoplayVoteDownEx (uint songQueueID, uint songQueueSongID);
  void autoplayVoteUpEx (uint songQueueID, uint songQueueSongID);
  void broadcastSong (QString message, QString link, QString username, QString password, uint songID, QString service, bool saveCredentials);
  void createWidgetIDFromSongIDs (QList<uint> songIDs);
  void deletePlaylist (uint playlistID);
  void favorite (uint id, QString what);
  void forgotPassword (void);
  void getAffiliateDownloadURLs (QString songName, QString artistName);
  void getArtistAutocomplete ();
  void getArtistByID (uint artistID);
  void getArtistsForTag (TagID tagID);
  void getAutoCoolPlaylistName ();
  void getCombinedFeedData (uint loggedInUserID, QDate day, QList<uint> userIDs);
  void getCommunicationToken ();
  void getContactInfoForFollowedUsers ();
  void getCountryFromRequestIP ();
  void getDetailsForBroadcast (uint songID);
  void getEmailAddress ();
  void getFavouriteIDs (uint userID, QString ofWhat);
  void getFavourites (uint userID, QString ofWhat);
  void getPlaylistByID ();
  void getQueueSongListFromSongIDs (QList<uint> songIDs);
  void getRecentlyActiveUsers ();
  void getSearchResults (QString searchTerm, QString type);
  void getSimilarUsers ();
  void getSongForAutoplayExt ();
  void getStationByID ();
  void getStreamKeyFromSongID (bool mobile, bool prefetch, uint songID);
  void getStreamKeyFromSongIDEx (bool mobile, bool prefetch, uint songID);
  void getTokenForSong (uint songID);
  void getUserByID ();
  void getUserSettings ();
  void getUserSidebar ();
  void initiateQueueEx ();
  void logoutUser ();
  void logTargetedThemeImpression ();
  void markSongAsDownloaded (uint streamServerID, QString streamKey, uint songID);
  void markSongComplete (uint streamServerID, QString streamKey, uint songID);
  void markSongQueueSongPlayed (uint songQueueID, uint songQueueSongID, uint streamServerID, QString streamKey, uint songID);
  void markSongSkipped (uint songQueueID, uint songQueueSongID);
  void markStreamKeyOver30Seconds (uint songQueueID, uint songQueueSongID, uint streamServerID, QString streamKey, uint songID);
  void overwriteExistingPlaylist (uint playlistID, QList<uint> songIDs);
  void playlistGetFans (uint playlistID);
  void popularGetSongs (QString type);
  void registerUserEx ();
  void removeSongsFromQueueExte (bool userRemoved, QList<uint> songQueueSongIDs, uint songQueueID);
  void renamePlaylist (uint playlistID, QString playlistName);
  void reportBroadcast ();
  void setPlaylistAbout (uint playlistID, QString about);
  void unFavorite (uint id, QString what);
  void updateLastfmService (QString token, int flagsRemove, QString username, QString session, int flagsAdd);
  void updateStreamKeyLength (uint streamServerID, uint songID, QString streamKey, float length);
  void userAddSongToLibrary ();
  void userGetFans ();
  void userGetLibraryTSModified ();
  void userGetPlaylists (uint userID);
  void userGetSongsInLibrary (QString page, uint userID);

private: // data
  std::shared_ptr<GrooveClient> m_client;
};
