void
GrooveService::markSongComplete (uint streamServerID, QString streamKey, uint songID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (markSongComplete_responded ()));
}

void
GrooveService::markSongComplete_responded ()
{
  GrooveReply result = getResult ();
}
