void
GrooveService::forgotPassword (void)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (forgotPassword_responded ()));
}

void
GrooveService::forgotPassword_responded ()
{
}
