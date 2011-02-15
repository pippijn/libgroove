void
GrooveService::artistGetAlbums ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (artistGetAlbums_responded ()));
}

void
GrooveService::artistGetAlbums_responded ()
{
  GrooveReply result = getResult ();
}
