void
GrooveService::getTokenForSong (uint songID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (getTokenForSong_responded ()));
}

void
GrooveService::getTokenForSong_responded ()
{
}
