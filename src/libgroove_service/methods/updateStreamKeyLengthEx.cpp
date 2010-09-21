void
GrooveService::updateStreamKeyLengthEx (QString streamKey, uint streamServerID, uint songID, float length)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (updateStreamKeyLengthEx_responded ()));
}

void
GrooveService::updateStreamKeyLengthEx_responded ()
{
}
