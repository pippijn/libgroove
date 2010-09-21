void
GrooveService::getUserFacebookData ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (getUserFacebookData_responded ()));
}

void
GrooveService::getUserFacebookData_responded ()
{
}
