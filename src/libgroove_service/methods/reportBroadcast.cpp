void
GrooveService::reportBroadcast ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (reportBroadcast_responded ()));
}

void
GrooveService::reportBroadcast_responded ()
{
}
