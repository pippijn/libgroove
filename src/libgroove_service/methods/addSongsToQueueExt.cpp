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

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "songQueueID", songQueueID },
     { "songIDsArtistIDs", songIDsArtistIDs },
  };

  request.post (this, SLOT (addSongsToQueueExt_responded ()));
  //request.post (parent (), m_slot);
}

void
GrooveService::addSongsToQueueExt_responded ()
{
}
