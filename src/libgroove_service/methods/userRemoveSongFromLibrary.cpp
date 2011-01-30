void
GrooveService::userRemoveSongFromLibrary ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (userRemoveSongFromLibrary_responded ()));
}

void
GrooveService::userRemoveSongFromLibrary_responded ()
{
}
