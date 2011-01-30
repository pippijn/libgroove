void
GrooveService::getGroovesharkUsersFromFacebookUserIDs ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getGroovesharkUsersFromFacebookUserIDs_responded ()));
}

void
GrooveService::getGroovesharkUsersFromFacebookUserIDs_responded ()
{
}
