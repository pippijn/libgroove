void
GrooveService::authenticateUser ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (authenticateUser_responded ()));
}

void
GrooveService::authenticateUser_responded ()
{
}
