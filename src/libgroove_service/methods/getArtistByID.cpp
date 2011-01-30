void
GrooveService::getArtistByID (uint artistID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getArtistByID_responded ()));
}

void
GrooveService::getArtistByID_responded ()
{
}
