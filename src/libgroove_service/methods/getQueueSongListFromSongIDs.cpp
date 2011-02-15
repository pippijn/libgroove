void
GrooveService::getQueueSongListFromSongIDs (QList<uint> songIDs)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "songIDs", songIDs },
  };

  request.post (this, SLOT (getQueueSongListFromSongIDs_responded ()));
}

void
GrooveService::getQueueSongListFromSongIDs_responded ()
{
  GrooveReply result = getResult ();
}
