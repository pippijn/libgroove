void
GrooveService::updateLastfmService (QString token, int flagsRemove, QString username, QString session, int flagsAdd)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (updateLastfmService_responded ()));
}

void
GrooveService::updateLastfmService_responded ()
{
}
