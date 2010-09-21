void
GrooveService::markSongQueueSongPlayed (uint songQueueID, uint songQueueSongID, uint streamServerID, QString streamKey, uint songID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (markSongQueueSongPlayed_responded ()));
}

void
GrooveService::markSongQueueSongPlayed_responded ()
{
}
