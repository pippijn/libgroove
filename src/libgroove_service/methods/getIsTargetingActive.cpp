void
GrooveService::getIsTargetingActive ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getIsTargetingActive_responded ()));
}

void
GrooveService::getIsTargetingActive_responded ()
{
  GrooveReply result = getResult ();
}
