void
GrooveService::markSongSkipped (uint songQueueID, uint songQueueSongID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (markSongSkipped_responded ()));
}

void
GrooveService::markSongSkipped_responded ()
{
}
