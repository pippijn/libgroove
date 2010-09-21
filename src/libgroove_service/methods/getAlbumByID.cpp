void
GrooveService::getAlbumByID ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (getAlbumByID_responded ()));
}

void
GrooveService::getAlbumByID_responded ()
{
}
