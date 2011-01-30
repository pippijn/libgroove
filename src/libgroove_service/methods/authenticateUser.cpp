void
GrooveService::authenticateUser (QString username, QString password, QString authToken)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "username", username },
    { "password", password },
    { "authToken", authToken },
  };

  request.post (this, SLOT (authenticateUser_responded ()));
}

void
GrooveService::authenticateUser_responded ()
{
}
