void
GrooveService::setPlaylistAbout (uint playlistID, QString about)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (setPlaylistAbout_responded ()));
}

void
GrooveService::setPlaylistAbout_responded ()
{
  GrooveReply result = getResult ();
}
