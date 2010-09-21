void
GrooveService::provideVIPFeedback ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (provideVIPFeedback_responded ()));
}

void
GrooveService::provideVIPFeedback_responded ()
{
}
