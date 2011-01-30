void
GrooveService::userAddSongToLibrary ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (userAddSongToLibrary_responded ()));
}

void
GrooveService::userAddSongToLibrary_responded ()
{
}
