void
GrooveService::autoplayVoteDownEx (uint songQueueID, uint songQueueSongID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (autoplayVoteDownEx_responded ()));
}

void
GrooveService::autoplayVoteDownEx_responded ()
{
}
