void
GrooveService::authenticateUserEx (QString password, QString username)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "password", password },
    { "username", username },
  };

  request.post (this, SLOT (authenticateUserEx_responded ()));
}

void
GrooveService::authenticateUserEx_responded ()
{
  GrooveReply result = getResult ();
}
