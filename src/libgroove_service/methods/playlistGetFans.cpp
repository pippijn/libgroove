void
GrooveService::playlistGetFans (uint playlistID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (playlistGetFans_responded ()));
}

void
GrooveService::playlistGetFans_responded ()
{
  GrooveReply result = getResult ();
}
