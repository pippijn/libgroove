void
GrooveService::getUserByID ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getUserByID_responded ()));
}

void
GrooveService::getUserByID_responded ()
{
}
