void
GrooveService::getAutoCoolPlaylistName ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (getAutoCoolPlaylistName_responded ()));
}

void
GrooveService::getAutoCoolPlaylistName_responded ()
{
}
