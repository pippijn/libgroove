void
GrooveService::getUserSettings ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getUserSettings_responded ()));
}

void
GrooveService::getUserSettings_responded ()
{
  GrooveReply result = getResult ();
}
