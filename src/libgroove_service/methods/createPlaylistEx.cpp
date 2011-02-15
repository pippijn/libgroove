void
GrooveService::createPlaylistEx ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (createPlaylistEx_responded ()));
}

void
GrooveService::createPlaylistEx_responded ()
{
  GrooveReply result = getResult ();
}
