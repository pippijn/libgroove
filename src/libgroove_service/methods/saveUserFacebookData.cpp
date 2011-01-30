void
GrooveService::saveUserFacebookData ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (saveUserFacebookData_responded ()));
}

void
GrooveService::saveUserFacebookData_responded ()
{
}
