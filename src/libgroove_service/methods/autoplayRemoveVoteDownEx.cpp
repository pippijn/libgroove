void
GrooveService::autoplayRemoveVoteDownEx (uint songQueueID, uint songQueueSongID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (autoplayRemoveVoteDownEx_responded ()));
}

void
GrooveService::autoplayRemoveVoteDownEx_responded ()
{
}
