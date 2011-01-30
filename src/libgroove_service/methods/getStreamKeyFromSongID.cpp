void
GrooveService::getStreamKeyFromSongID (bool mobile, bool prefetch, uint songID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getStreamKeyFromSongID_responded ()));
}

void
GrooveService::getStreamKeyFromSongID_responded ()
{
}
