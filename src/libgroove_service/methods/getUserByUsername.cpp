void
GrooveService::getUserByUsername ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (getUserByUsername_responded ()));
}

void
GrooveService::getUserByUsername_responded ()
{
}
