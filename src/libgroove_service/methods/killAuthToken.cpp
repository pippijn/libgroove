void
GrooveService::killAuthToken ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (killAuthToken_responded ()));
}

void
GrooveService::killAuthToken_responded ()
{
  GrooveReply result = getResult ();
}
