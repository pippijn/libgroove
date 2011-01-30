void
GrooveService::updateStreamKeyLength (QString streamKey, uint streamServerID, uint songID, float length)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (updateStreamKeyLength_responded ()));
}

void
GrooveService::updateStreamKeyLength_responded ()
{
}
