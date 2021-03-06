void
GrooveService::autoplayVoteUp ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (autoplayVoteUp_responded ()));
}

void
GrooveService::autoplayVoteUp_responded ()
{
  GrooveReply result = getResult ();
}
