void
GrooveService::userAddSongsToLibrary ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (userAddSongsToLibrary_responded ()));
}

void
GrooveService::userAddSongsToLibrary_responded ()
{
}
