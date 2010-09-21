void
GrooveService::authenticateUserEx (QString password, QString username)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
    { "password", password },
    { "username", username },
  };

  //request.post (this, SLOT (authenticateUserEx_responded ()));
  request.post (parent (), m_slot);
}

void
GrooveService::authenticateUserEx_responded ()
{
}
