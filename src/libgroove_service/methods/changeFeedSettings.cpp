void
GrooveService::changeFeedSettings ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (changeFeedSettings_responded ()));
}

void
GrooveService::changeFeedSettings_responded ()
{
  GrooveReply result = getResult ();
}
