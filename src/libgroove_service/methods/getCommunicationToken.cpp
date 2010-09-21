void
GrooveService::getCommunicationToken ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (getCommunicationToken_responded ()));
}

void
GrooveService::getCommunicationToken_responded ()
{
}
