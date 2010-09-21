void
GrooveService::autoplayRemoveVoteUpEx (uint songQueueID, uint songQueueSongID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (autoplayRemoveVoteUpEx_responded ()));
}

void
GrooveService::autoplayRemoveVoteUpEx_responded ()
{
}
