void
GrooveService::autoplayGetSong (uint songQueueID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "songQueueID", uint (songQueueID) },
  };

  request.post (this, SLOT (autoplayGetSong_responded ()));
}

void
GrooveService::autoplayGetSong_responded ()
{
  GrooveReply result = getResult ();
}
