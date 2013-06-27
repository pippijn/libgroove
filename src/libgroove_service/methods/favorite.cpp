void
GrooveService::favorite (uint id, QString what)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (favorite_responded ()));
}

void
GrooveService::favorite_responded ()
{
  GrooveReply result = getResult ();
}
