void
GrooveService::changeUserInfo ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (changeUserInfo_responded ()));
}

void
GrooveService::changeUserInfo_responded ()
{
}
