void
GrooveService::getLastfmService ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getLastfmService_responded ()));
}

void
GrooveService::getLastfmService_responded ()
{
}
