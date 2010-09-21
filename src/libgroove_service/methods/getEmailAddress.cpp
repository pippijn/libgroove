void
GrooveService::getEmailAddress ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (getEmailAddress_responded ()));
}

void
GrooveService::getEmailAddress_responded ()
{
}
