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

  typedef uint UserID;
  typedef uint SongID;
  typedef uint AlbumID;

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
