void
GrooveService::playlistUndelete ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (playlistUndelete_responded ()));
}

void
GrooveService::playlistUndelete_responded ()
{
}
