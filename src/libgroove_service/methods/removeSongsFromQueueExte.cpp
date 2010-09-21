void
GrooveService::removeSongsFromQueueExte (bool userRemoved, QList<uint> songQueueSongIDs, uint songQueueID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (removeSongsFromQueueExte_responded ()));
}

void
GrooveService::removeSongsFromQueueExte_responded ()
{
}
