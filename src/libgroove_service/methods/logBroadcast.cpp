void
GrooveService::logBroadcast ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (logBroadcast_responded ()));
}

void
GrooveService::logBroadcast_responded ()
{
}
