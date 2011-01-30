void
GrooveService::getCountry ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getCountry_responded ()));
}

void
GrooveService::getCountry_responded ()
{
}
