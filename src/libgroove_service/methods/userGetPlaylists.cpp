void
GrooveService::userGetPlaylists (uint userID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (userGetPlaylists_responded ()));
}

void
GrooveService::userGetPlaylists_responded ()
{
}
