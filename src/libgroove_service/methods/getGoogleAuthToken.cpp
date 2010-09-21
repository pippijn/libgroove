void
GrooveService::getGoogleAuthToken ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (getGoogleAuthToken_responded ()));
}

void
GrooveService::getGoogleAuthToken_responded ()
{
}
