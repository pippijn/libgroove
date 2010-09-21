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

  GrooveService (GrooveService const &rhs) = delete;
  GrooveService &operator = (GrooveService const &rhs) = delete;

private: // types
  typedef QVariantOrMap::pair pair;
  typedef QVariantOrMap::map map;
  typedef QVariantOrMap::array array;

public: // ctor/dtor
  GrooveService (std::shared_ptr<GrooveClient> client, char const *slot, QObject *parent);
  ~GrooveService ();

private: // functions
  pair country () const;
  map header (char const *method) const;

  QVariantMap getReply () const;

private slots:
  void addSongsToQueueExt_responded ();
  void artistGetFans_responded ();
  void artistGetSimilarArtists_responded ();
  void artistGetSongs_responded ();
  void authenticateUserEx_responded ();
  void autoplayGetSong_responded ();
  void autoplayRemoveVoteDownEx_responded ();
  void autoplayRemoveVoteUpEx_responded ();
  void autoplayVoteDownEx_responded ();
  void autoplayVoteUpEx_responded ();
  void broadcastSong_responded ();
  void createWidgetIDFromSongIDs_responded ();
  void deletePlaylist_responded ();
  void favorite_responded ();
  void forgotPassword_responded ();
  void getAffiliateDownloadURLs_responded ();
  void getArtistAutocomplete_responded ();
  void getArtistByID_responded ();
  void getArtistsForTag_responded ();
  void getAutoCoolPlaylistName_responded ();
  void getCombinedFeedData_responded ();
  void getCommunicationToken_responded ();
  void getContactInfoForFollowedUsers_responded ();
  void getCountryFromRequestIP_responded ();
  void getDetailsForBroadcast_responded ();
  void getEmailAddress_responded ();
  void getFavouriteIDs_responded ();
  void getFavourites_responded ();
  void getPlaylistByID_responded ();
  void getQueueSongListFromSongIDs_responded ();
  void getRecentlyActiveUsers_responded ();
  void getSearchResults_responded ();
  void getSimilarUsers_responded ();
  void getSongForAutoplayExt_responded ();
  void getStationByID_responded ();
  void getStreamKeyFromSongID_responded ();
  void getStreamKeyFromSongIDEx_responded ();
  void getTokenForSong_responded ();
  void getUserByID_responded ();
  void getUserSettings_responded ();
  void getUserSidebar_responded ();
  void initiateQueueEx_responded ();
  void logoutUser_responded ();
  void logTargetedThemeImpression_responded ();
  void markSongAsDownloaded_responded ();
  void markSongComplete_responded ();
  void markSongQueueSongPlayed_responded ();
  void markSongSkipped_responded ();
  void markStreamKeyOver30Seconds_responded ();
  void overwriteExistingPlaylist_responded ();
  void playlistGetFans_responded ();
  void popularGetSongs_responded ();
  void registerUserEx_responded ();
  void removeSongsFromQueueExte_responded ();
  void renamePlaylist_responded ();
  void reportBroadcast_responded ();
  void setPlaylistAbout_responded ();
  void unFavorite_responded ();
  void updateLastfmService_responded ();
  void updateStreamKeyLength_responded ();
  void userAddSongToLibrary_responded ();
  void userGetFans_responded ();
  void userGetLibraryTSModified_responded ();
  void userGetPlaylists_responded ();
  void userGetSongsInLibrary_responded ();

public slots: // functions
  void addSongsToQueueExt (uint songQueueID, map songIDsArtistIDs);
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
  char const *m_slot;

signals:
  void streamKeyReady (QString ip, QString streamKey);
};
