#include "request.h"

#include "groove/service.h"

#include "addSongsToQueueExt.cpp"
#include "artistGetFans.cpp"


void
GrooveService::artistGetSimilarArtists (uint artistID)
{
}

void
GrooveService::artistGetSimilarArtists_responded ()
{
}

void
GrooveService::artistGetSongs (uint offset, uint artistID, bool isVerified)
{
}

void
GrooveService::artistGetSongs_responded ()
{
}

#include "authenticateUserEx.cpp"

void
GrooveService::autoplayGetSong (uint songQueueID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
    { "songQueueID", uint (songQueueID) },
    country (),
  };

  request.post (this, SLOT (autoplayGetSong_responded ()));
}

void
GrooveService::autoplayGetSong_responded ()
{
  QVariantMap reply = getReply ();

  QVariantList result = reply["result"].toList ();

  //emit streamKeyReady (ip, streamKey);
}

void
GrooveService::autoplayRemoveVoteDownEx (uint songQueueID, uint songQueueSongID)
{
}

void
GrooveService::autoplayRemoveVoteDownEx_responded ()
{
}

void
GrooveService::autoplayRemoveVoteUpEx (uint songQueueID, uint songQueueSongID)
{
}

void
GrooveService::autoplayRemoveVoteUpEx_responded ()
{
}

void
GrooveService::autoplayVoteDownEx (uint songQueueID, uint songQueueSongID)
{
}

void
GrooveService::autoplayVoteDownEx_responded ()
{
}

void
GrooveService::autoplayVoteUpEx (uint songQueueID, uint songQueueSongID)
{
}

void
GrooveService::autoplayVoteUpEx_responded ()
{
}

void
GrooveService::broadcastSong (QString message, QString link, QString username, QString password, uint songID, QString service, bool saveCredentials)
{
}

void
GrooveService::broadcastSong_responded ()
{
}

void
GrooveService::createWidgetIDFromSongIDs (QList<uint> songIDs)
{
}

void
GrooveService::createWidgetIDFromSongIDs_responded ()
{
}

void
GrooveService::deletePlaylist (uint playlistID)
{
}

void
GrooveService::deletePlaylist_responded ()
{
}

void
GrooveService::favorite (uint id, QString what)
{
}

void
GrooveService::favorite_responded ()
{
}

void
GrooveService::flagSong (QString streamKey, uint streamServerID, uint songID, uint reason)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
    { "streamKey", streamKey },
    { "streamServerID", streamServerID },
    { "songID", songID },
    { "reason", reason },
  };

  request.post (this, SLOT (flagSong_responded ()));
}

void
GrooveService::flagSong_responded ()
{
}

void
GrooveService::forgotPassword (void)
{
}

void
GrooveService::forgotPassword_responded ()
{
}

void
GrooveService::getAffiliateDownloadURLs (QString songName, QString artistName)
{
}

void
GrooveService::getAffiliateDownloadURLs_responded ()
{
}

void
GrooveService::getArtistAutocomplete ()
{
}

void
GrooveService::getArtistAutocomplete_responded ()
{
}

void
GrooveService::getArtistByID (uint artistID)
{
}

void
GrooveService::getArtistByID_responded ()
{
}

void
GrooveService::getArtistsForTag (TagID tagID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
    { "tagID", uint (tagID) },
  };

  request.post (this, SLOT (getArtistsForTag_responded ()));
}

void
GrooveService::getArtistsForTag_responded ()
{
  QVariantMap reply = getReply ();

  QVariantList result = reply["result"].toList ();

  //emit streamKeyReady (ip, streamKey);
}

void
GrooveService::getAutoCoolPlaylistName ()
{
}

void
GrooveService::getAutoCoolPlaylistName_responded ()
{
}

void
GrooveService::getCombinedFeedData (uint loggedInUserID, QDate day, QList<uint> userIDs)
{
}

void
GrooveService::getCombinedFeedData_responded ()
{
}

void
GrooveService::getCommunicationToken ()
{
}

void
GrooveService::getCommunicationToken_responded ()
{
}

void
GrooveService::getContactInfoForFollowedUsers ()
{
}

void
GrooveService::getContactInfoForFollowedUsers_responded ()
{
}

void
GrooveService::getCountryFromRequestIP ()
{
}

void
GrooveService::getCountryFromRequestIP_responded ()
{
}

void
GrooveService::getDetailsForBroadcast (uint songID)
{
}

void
GrooveService::getDetailsForBroadcast_responded ()
{
}

void
GrooveService::getEmailAddress ()
{
}

void
GrooveService::getEmailAddress_responded ()
{
}

void
GrooveService::getFavouriteIDs (uint userID, QString ofWhat)
{
}

void
GrooveService::getFavouriteIDs_responded ()
{
}

void
GrooveService::getFavourites (uint userID, QString ofWhat)
{
}

void
GrooveService::getFavourites_responded ()
{
}

void
GrooveService::getPlaylistByID ()
{
}

void
GrooveService::getPlaylistByID_responded ()
{
}

void
GrooveService::getQueueSongListFromSongIDs (QList<uint> songIDs)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
    { "songIDs", songIDs },
  };

  request.post (this, SLOT (flagSong_responded ()));
}

void
GrooveService::getQueueSongListFromSongIDs_responded ()
{
}

void
GrooveService::getRecentlyActiveUsers ()
{
}

void
GrooveService::getRecentlyActiveUsers_responded ()
{
}

#include "getSearchResults.cpp"

void
GrooveService::getSimilarUsers ()
{
}

void
GrooveService::getSimilarUsers_responded ()
{
}

void
GrooveService::getSongForAutoplayExt ()
{
}

void
GrooveService::getSongForAutoplayExt_responded ()
{
}

void
GrooveService::getStationByID ()
{
}

void
GrooveService::getStationByID_responded ()
{
}

void
GrooveService::getStreamKeyFromSongID (bool mobile, bool prefetch, uint songID)
{
}

void
GrooveService::getStreamKeyFromSongID_responded ()
{
}

#include "getStreamKeyFromSongIDEx.cpp"

void
GrooveService::getTokenForSong (uint songID)
{
}

void
GrooveService::getTokenForSong_responded ()
{
}

void
GrooveService::getUserByID ()
{
}

void
GrooveService::getUserByID_responded ()
{
}

void
GrooveService::getUserSettings ()
{
}

void
GrooveService::getUserSettings_responded ()
{
}

void
GrooveService::getUserSidebar ()
{
}

void
GrooveService::getUserSidebar_responded ()
{
}

void
GrooveService::initiateQueueEx ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters ();

  request.post (this, SLOT (playlistGetSongs_responded ()));
}

void
GrooveService::initiateQueueEx_responded ()
{
  QVariantMap reply = getReply ();

  QString queueID = reply["result"].toString ();

  //emit streamKeyReady (ip, streamKey);
}

#include "logoutUser.cpp"

void
GrooveService::logTargetedThemeImpression ()
{
}

void
GrooveService::logTargetedThemeImpression_responded ()
{
}

void
GrooveService::markSongComplete (uint streamServerID, QString streamKey, uint songID)
{
}

void
GrooveService::markSongComplete_responded ()
{
}

void
GrooveService::markSongDownloadedEx (uint streamServerID, QString streamKey, uint songID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
    { "streamKey", streamKey },
    { "streamServerID", streamServerID },
    { "songID", songID },
  };

  request.post (this, SLOT (playlistGetSongs_responded ()));
}

void
GrooveService::markSongDownloadedEx_responded ()
{
}

void
GrooveService::markSongQueueSongPlayed (uint songQueueID, uint songQueueSongID, uint streamServerID, QString streamKey, uint songID)
{
}

void
GrooveService::markSongQueueSongPlayed_responded ()
{
}

void
GrooveService::markSongSkipped (uint songQueueID, uint songQueueSongID)
{
}

void
GrooveService::markSongSkipped_responded ()
{
}

void
GrooveService::markStreamKeyOver30Seconds (uint songQueueID, uint songQueueSongID, uint streamServerID, QString streamKey, uint songID)
{
}

void
GrooveService::markStreamKeyOver30Seconds_responded ()
{
}

void
GrooveService::overwriteExistingPlaylist (uint playlistID, QList<uint> songIDs)
{
}

void
GrooveService::overwriteExistingPlaylist_responded ()
{
}

void
GrooveService::playlistGetFans (uint playlistID)
{
}

void
GrooveService::playlistGetFans_responded ()
{
}

void
GrooveService::playlistGetSongs (uint playlistID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
    { "playlistID", playlistID },
  };

  request.post (this, SLOT (playlistGetSongs_responded ()));
}

void
GrooveService::playlistGetSongs_responded ()
{
  QVariantMap reply = getReply ();

  QVariantMap result = reply["result"].toMap ();

  QVariantList Songs = result["Songs"].toList ();

  //emit streamKeyReady (ip, streamKey);
}

void
GrooveService::popularGetSongs (QString type)
{
}

void
GrooveService::popularGetSongs_responded ()
{
}

void
GrooveService::registerUserEx ()
{
}

void
GrooveService::registerUserEx_responded ()
{
}

void
GrooveService::removeSongsFromQueueExte (bool userRemoved, QList<uint> songQueueSongIDs, uint songQueueID)
{
}

void
GrooveService::removeSongsFromQueueExte_responded ()
{
}

void
GrooveService::renamePlaylist (uint playlistID, QString playlistName)
{
}

void
GrooveService::renamePlaylist_responded ()
{
}

void
GrooveService::reportBroadcast ()
{
}

void
GrooveService::reportBroadcast_responded ()
{
}

void
GrooveService::setPlaylistAbout (uint playlistID, QString about)
{
}

void
GrooveService::setPlaylistAbout_responded ()
{
}

void
GrooveService::unFavorite (uint id, QString what)
{
}

void
GrooveService::unFavorite_responded ()
{
}

void
GrooveService::updateLastfmService (QString token, int flagsRemove, QString username, QString session, int flagsAdd)
{
}

void
GrooveService::updateLastfmService_responded ()
{
}

void
GrooveService::updateStreamKeyLength (QString streamKey, uint streamServerID, uint songID, float length)
{
}

void
GrooveService::updateStreamKeyLength_responded ()
{
}

void
GrooveService::updateStreamKeyLengthEx (QString streamKey, uint streamServerID, uint songID, float length)
{
}

void
GrooveService::updateStreamKeyLengthEx_responded ()
{
}

void
GrooveService::userAddSongToLibrary ()
{
}

void
GrooveService::userAddSongToLibrary_responded ()
{
}

void
GrooveService::userGetFans ()
{
}

void
GrooveService::userGetFans_responded ()
{
}

void
GrooveService::userGetLibraryTSModified ()
{
}

void
GrooveService::userGetLibraryTSModified_responded ()
{
}

void
GrooveService::userGetPlaylists (uint userID)
{
}

void
GrooveService::userGetPlaylists_responded ()
{
}

void
GrooveService::userGetSongsInLibrary (QString page, uint userID)
{
}

void
GrooveService::userGetSongsInLibrary_responded ()
{
}
