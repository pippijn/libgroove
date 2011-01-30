void
GrooveService::getPlaylistByID ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getPlaylistByID_responded ()));
}

void
GrooveService::getPlaylistByID_responded ()
{
}
