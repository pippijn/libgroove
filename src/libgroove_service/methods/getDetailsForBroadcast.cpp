void
GrooveService::getDetailsForBroadcast (uint songID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getDetailsForBroadcast_responded ()));
}

void
GrooveService::getDetailsForBroadcast_responded ()
{
}
