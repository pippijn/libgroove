void
GrooveService::provideSongFeedbackVote ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (provideSongFeedbackVote_responded ()));
}

void
GrooveService::provideSongFeedbackVote_responded ()
{
  GrooveReply result = getResult ();
}
