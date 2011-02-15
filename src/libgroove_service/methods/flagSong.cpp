void
GrooveService::flagSong (QString streamKey, uint streamServerID, uint songID, uint reason)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

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
  GrooveReply result = getResult ();
}
