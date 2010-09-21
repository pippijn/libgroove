void
GrooveService::removeUserFacebookData ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (removeUserFacebookData_responded ()));
}

void
GrooveService::removeUserFacebookData_responded ()
{
}
