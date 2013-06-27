void
GrooveService::getTokenForSong (uint songID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getTokenForSong_responded ()));
}

void
GrooveService::getTokenForSong_responded ()
{
  GrooveReply result = getResult ();
}
