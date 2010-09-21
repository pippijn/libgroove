void
GrooveService::provideSongFeedbackMessage ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (provideSongFeedbackMessage_responded ()));
}

void
GrooveService::provideSongFeedbackMessage_responded ()
{
}
