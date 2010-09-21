void
GrooveService::autoplayVoteDown ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (autoplayVoteDown_responded ()));
}

void
GrooveService::autoplayVoteDown_responded ()
{
}
