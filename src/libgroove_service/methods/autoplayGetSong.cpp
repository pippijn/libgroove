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
