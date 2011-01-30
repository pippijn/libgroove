void
GrooveService::registerUser ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (registerUser_responded ()));
}

void
GrooveService::registerUser_responded ()
{
}
