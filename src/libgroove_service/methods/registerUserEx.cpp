void
GrooveService::registerUserEx ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (registerUserEx_responded ()));
}

void
GrooveService::registerUserEx_responded ()
{
}
