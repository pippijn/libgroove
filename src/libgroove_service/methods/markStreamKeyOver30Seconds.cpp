void
GrooveService::markStreamKeyOver30Seconds (uint songQueueID, uint songQueueSongID, uint streamServerID, QString streamKey, uint songID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (markStreamKeyOver30Seconds_responded ()));
}

void
GrooveService::markStreamKeyOver30Seconds_responded ()
{
}
