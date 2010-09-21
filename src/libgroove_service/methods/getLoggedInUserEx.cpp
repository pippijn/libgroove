void
GrooveService::getLoggedInUserEx ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (getLoggedInUserEx_responded ()));
}

void
GrooveService::getLoggedInUserEx_responded ()
{
}
