void
GrooveService::artistGetSongkickEvents ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (artistGetSongkickEvents_responded ()));
}

void
GrooveService::artistGetSongkickEvents_responded ()
{
}
