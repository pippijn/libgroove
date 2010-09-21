void
GrooveService::getUserSettings ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (getUserSettings_responded ()));
}

void
GrooveService::getUserSettings_responded ()
{
}
