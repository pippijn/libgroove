void
GrooveService::getCountryFromRequestIP ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (getCountryFromRequestIP_responded ()));
}

void
GrooveService::getCountryFromRequestIP_responded ()
{
}
