void
GrooveService::doHPBeatsNotification ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (doHPBeatsNotification_responded ()));
}

void
GrooveService::doHPBeatsNotification_responded ()
{
  GrooveReply result = getResult ();
}
