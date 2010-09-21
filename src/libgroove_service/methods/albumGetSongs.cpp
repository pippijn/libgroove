void
GrooveService::albumGetSongs ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (albumGetSongs_responded ()));
}

void
GrooveService::albumGetSongs_responded ()
{
}
