void
GrooveService::getSongFromToken ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getSongFromToken_responded ()));
}

void
GrooveService::getSongFromToken_responded ()
{
  GrooveReply result = getResult ();
}
