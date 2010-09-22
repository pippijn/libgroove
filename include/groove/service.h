/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

#include "groove/data/songptr.h"
#include "groove/private/make_varmap.h"
class GrooveClient;

#include <QDate>
#include <QList>
#include <QVariant>

#include <memory>

enum class TagID
{
  Rap           =    3,
  RnB           =    4,
  Rock          =   12,
  Alternative   =   13,
  Metal         =   17,
  HipHop        =   29,
  Jazz          =   43,
  Pop           =   56,
  Electronica   =   67,
  Trance        =   69,
  Ambient       =   75,
  Country       =   80,
  Bluegrass     =   96,
  Oldies        =  102,
  Punk          =  111,
  Folk          =  122,
  Indie         =  136,
  Reggae        =  160,
  Experimental  =  191,
  Blues         =  230,
  Latin         =  528,
  Classical     =  750,
  ClassicRock   = 3529,
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
  GrooveService (std::shared_ptr<GrooveClient> client, QObject *parent);
  ~GrooveService ();

private: // functions
  pair country () const;
  map header (char const *method) const;

  QVariantMap getReply () const;

private slots:
  void addShortcutToUserSidebar_responded ();
  void addSongsToQueueExt_responded ();
  void albumGetFans_responded ();
  void albumGetSongs_responded ();
  void artistGetAlbums_responded ();
  void artistGetFans_responded ();
  void artistGetSimilarArtists_responded ();
  void artistGetSongkickEvents_responded ();
  void artistGetSongs_responded ();
  void authenticateUser_responded ();
  void authenticateUserEx_responded ();
  void autoplayGetSong_responded ();
  void autoplayRemoveVoteDownEx_responded ();
  void autoplayRemoveVoteUpEx_responded ();
  void autoplayVoteDown_responded ();
  void autoplayVoteDownEx_responded ();
  void autoplayVoteUp_responded ();
  void autoplayVoteUpEx_responded ();
  void broadcastSong_responded ();
  void changeFeedSettings_responded ();
  void changeFollowFlags_responded ();
  void changeNotificationSettings_responded ();
  void changePassword_responded ();
  void changePrivacySettings_responded ();
  void changeUserInfo_responded ();
  void createPlaylistEx_responded ();
  void createWidgetIDFromSongIDs_responded ();
  void deletePlaylist_responded ();
  void doHPBeatsNotification_responded ();
  void doHPBeatsUpgrade_responded ();
  void favorite_responded ();
  void feedsRemoveEventFromProfile_responded ();
  void flagSong_responded ();
  void forgotPassword_responded ();
  void getAffiliateDownloadURLs_responded ();
  void getAlbumByID_responded ();
  void getArtistAutocomplete_responded ();
  void getArtistByID_responded ();
  void getArtistsForTag_responded ();
  void getAutoCoolPlaylistName_responded ();
  void getCombinedFeedData_responded ();
  void getCombinedProcessedFeedData_responded ();
  void getCommunicationToken_responded ();
  void getContactInfoForFollowedUsers_responded ();
  void getContactInfoForFollowers_responded ();
  void getCountry_responded ();
  void getCountryFromRequestIP_responded ();
  void getDetailsForBroadcast_responded ();
  void getEmailAddress_responded ();
  void getFavoriteIDs_responded ();
  void getFavorites_responded ();
  void getGoogleAuthToken_responded ();
  void getGoogleContacts_responded ();
  void getGroovesharkUsersFromFacebookUserIDs_responded ();
  void getIsTargetingActive_responded ();
  void getLastfmService_responded ();
  void getLoggedInUserEx_responded ();
  void getPlaylistByID_responded ();
  void getProcessedUserFeedData_responded ();
  void getQueueSongListFromSongIDs_responded ();
  void getRecentlyActiveUsers_responded ();
  void getSearchResults_responded ();
  void getSearchResultsEx_responded ();
  void getSearchSuggestion_responded ();
  void getServiceStatus_responded ();
  void getSimilarUsers_responded ();
  void getSongForAutoplayExt_responded ();
  void getSongFromToken_responded ();
  void getStationByID_responded ();
  void getStreamKeyFromSongID_responded ();
  void getStreamKeyFromSongIDEx_responded ();
  void getThumbplayRingtoneSearchResults_responded ();
  void getTokenForSong_responded ();
  void getUserByID_responded ();
  void getUserByInviteID_responded ();
  void getUserByUsername_responded ();
  void getUserFacebookData_responded ();
  void getUserSettings_responded ();
  void getUserSidebar_responded ();
  void initiateQueueEx_responded ();
  void killAuthToken_responded ();
  void logBroadcast_responded ();
  void logHomepageView_responded ();
  void logoutUser_responded ();
  void logTargetedThemeImpression_responded ();
  void logThemeOutboundLinkClick_responded ();
  void markSongComplete_responded ();
  void markSongDownloadedEx_responded ();
  void markSongQueueSongPlayed_responded ();
  void markSongSkipped_responded ();
  void markStreamKeyOver30Seconds_responded ();
  void overwriteExistingPlaylist_responded ();
  void playlistGetFans_responded ();
  void playlistGetSongs_responded ();
  void playlistUndelete_responded ();
  void popularGetSongs_responded ();
  void provideSongFeedbackMessage_responded ();
  void provideSongFeedbackVote_responded ();
  void provideVIPFeedback_responded ();
  void registerUser_responded ();
  void registerUserEx_responded ();
  void removeItemFromCommunityFeed_responded ();
  void removeLastfmService_responded ();
  void removeShortcutFromUserSidebar_responded ();
  void removeSongsFromQueueExte_responded ();
  void removeUserFacebookData_responded ();
  void renamePlaylist_responded ();
  void reportBroadcast_responded ();
  void saveUserFacebookData_responded ();
  void sendHPBeatsSMS_responded ();
  void sendInvites_responded ();
  void sendMobileAppSMS_responded ();
  void sendShare_responded ();
  void setPlaylistAbout_responded ();
  void songGetFans_responded ();
  void unfavorite_responded ();
  void updateLastfmService_responded ();
  void updateStreamKeyLength_responded ();
  void updateStreamKeyLengthEx_responded ();
  void userAddSongsToLibrary_responded ();
  void userAddSongToLibrary_responded ();
  void userGetFans_responded ();
  void userGetLibraryTSModified_responded ();
  void userGetPlaylists_responded ();
  void userGetSongsInLibrary_responded ();
  void userRemoveSongFromLibrary_responded ();

public slots: // functions
  void addShortcutToUserSidebar ();
  void addSongsToQueueExt (uint songQueueID, map songIDsArtistIDs);
  void albumGetFans ();
  void albumGetSongs ();
  void artistGetAlbums ();
  void artistGetFans (uint offset, uint artistID);
  void artistGetSimilarArtists (uint artistID);
  void artistGetSongkickEvents ();
  void artistGetSongs (uint offset, uint artistID, bool isVerified);
  void authenticateUser (QString username, QString password, QString authToken);
  void authenticateUserEx (QString password, QString username);
  void autoplayGetSong (uint songQueueID);
  void autoplayRemoveVoteDownEx (uint songQueueID, uint songQueueSongID);
  void autoplayRemoveVoteUpEx (uint songQueueID, uint songQueueSongID);
  void autoplayVoteDown ();
  void autoplayVoteDownEx (uint songQueueID, uint songQueueSongID);
  void autoplayVoteUp ();
  void autoplayVoteUpEx (uint songQueueID, uint songQueueSongID);
  void broadcastSong (QString message, QString link, QString username, QString password, uint songID, QString service, bool saveCredentials);
  void changeFeedSettings ();
  void changeFollowFlags ();
  void changeNotificationSettings ();
  void changePassword ();
  void changePrivacySettings ();
  void changeUserInfo ();
  void createPlaylistEx ();
  void createWidgetIDFromSongIDs (QList<uint> songIDs);
  void deletePlaylist (uint playlistID);
  void doHPBeatsNotification ();
  void doHPBeatsUpgrade ();
  void favorite (uint id, QString what);
  void feedsRemoveEventFromProfile ();
  void flagSong (QString streamKey, uint streamServerID, uint songID, uint reason);
  void forgotPassword (void);
  void getAffiliateDownloadURLs (QString songName, QString artistName);
  void getAlbumByID ();
  void getArtistAutocomplete ();
  void getArtistByID (uint artistID);
  void getArtistsForTag (TagID tagID);
  void getAutoCoolPlaylistName ();
  void getCombinedFeedData (uint loggedInUserID, QDate day, QList<uint> userIDs);
  void getCombinedProcessedFeedData ();
  void getCommunicationToken ();
  void getContactInfoForFollowedUsers ();
  void getContactInfoForFollowers ();
  void getCountry ();
  void getCountryFromRequestIP ();
  void getDetailsForBroadcast (uint songID);
  void getEmailAddress ();
  void getFavoriteIDs (uint userID, QString ofWhat);
  void getFavorites (uint userID, QString ofWhat);
  void getGoogleAuthToken ();
  void getGoogleContacts ();
  void getGroovesharkUsersFromFacebookUserIDs ();
  void getIsTargetingActive ();
  void getLastfmService ();
  void getLoggedInUserEx ();
  void getPlaylistByID ();
  void getProcessedUserFeedData ();
  void getQueueSongListFromSongIDs (QList<uint> songIDs);
  void getRecentlyActiveUsers ();
  void getSearchResultsEx ();
  void getSearchResults (QString searchTerm, QString type);
  void getSearchSuggestion ();
  void getServiceStatus ();
  void getSimilarUsers ();
  void getSongForAutoplayExt ();
  void getSongFromToken ();
  void getStationByID ();
  void getStreamKeyFromSongID (bool mobile, bool prefetch, uint songID);
  void getStreamKeyFromSongIDEx (bool mobile, bool prefetch, uint songID);
  void getThumbplayRingtoneSearchResults ();
  void getTokenForSong (uint songID);
  void getUserByID ();
  void getUserByInviteID ();
  void getUserByUsername ();
  void getUserFacebookData ();
  void getUserSettings ();
  void getUserSidebar ();
  void initiateQueueEx ();
  void killAuthToken ();
  void logBroadcast ();
  void logHomepageView ();
  void logoutUser ();
  void logTargetedThemeImpression ();
  void logThemeOutboundLinkClick ();
  void markSongComplete (uint streamServerID, QString streamKey, uint songID);
  void markSongDownloadedEx (uint streamServerID, QString streamKey, uint songID);
  void markSongQueueSongPlayed (uint songQueueID, uint songQueueSongID, uint streamServerID, QString streamKey, uint songID);
  void markSongSkipped (uint songQueueID, uint songQueueSongID);
  void markStreamKeyOver30Seconds (uint songQueueID, uint songQueueSongID, uint streamServerID, QString streamKey, uint songID);
  void overwriteExistingPlaylist (uint playlistID, QList<uint> songIDs);
  void playlistGetFans (uint playlistID);
  void playlistGetSongs (uint playlistID);
  void playlistUndelete ();
  void popularGetSongs (QString type);
  void provideSongFeedbackMessage ();
  void provideSongFeedbackVote ();
  void provideVIPFeedback ();
  void registerUser ();
  void registerUserEx ();
  void removeItemFromCommunityFeed ();
  void removeLastfmService ();
  void removeShortcutFromUserSidebar ();
  void removeSongsFromQueueExte (bool userRemoved, QList<uint> songQueueSongIDs, uint songQueueID);
  void removeUserFacebookData ();
  void renamePlaylist (uint playlistID, QString playlistName);
  void reportBroadcast ();
  void saveUserFacebookData ();
  void sendHPBeatsSMS ();
  void sendInvites ();
  void sendMobileAppSMS ();
  void sendShare ();
  void setPlaylistAbout (uint playlistID, QString about);
  void songGetFans ();
  void unfavorite (uint id, QString what);
  void updateLastfmService (QString token, int flagsRemove, QString username, QString session, int flagsAdd);
  void updateStreamKeyLengthEx (QString streamKey, uint streamServerID, uint songID, float length);
  void updateStreamKeyLength (QString streamKey, uint streamServerID, uint songID, float length);
  void userAddSongsToLibrary ();
  void userAddSongToLibrary ();
  void userGetFans ();
  void userGetLibraryTSModified ();
  void userGetPlaylists (uint userID);
  void userGetSongsInLibrary (QString page, uint userID);
  void userRemoveSongFromLibrary ();

private: // data
  std::shared_ptr<GrooveClient> m_client;

signals:
  void searchResultsReady (QList<GrooveSongPointer> const &songList);
  void streamKeyReady (QString ip, QString streamKey);
};
