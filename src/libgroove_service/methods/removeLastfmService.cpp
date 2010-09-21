void
GrooveService::removeLastfmService ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (removeLastfmService_responded ()));
}

void
GrooveService::removeLastfmService_responded ()
{
}
