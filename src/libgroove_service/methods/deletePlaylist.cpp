void
GrooveService::deletePlaylist (uint playlistID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (deletePlaylist_responded ()));
}

void
GrooveService::deletePlaylist_responded ()
{
}
