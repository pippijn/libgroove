void
GrooveService::userGetSongsInLibrary (QString page, uint userID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (userGetSongsInLibrary_responded ()));
}

void
GrooveService::userGetSongsInLibrary_responded ()
{
}
