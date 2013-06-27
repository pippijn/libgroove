void
GrooveService::feedsRemoveEventFromProfile ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (feedsRemoveEventFromProfile_responded ()));
}

void
GrooveService::feedsRemoveEventFromProfile_responded ()
{
  GrooveReply result = getResult ();
}
