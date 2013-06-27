void
GrooveService::sendHPBeatsSMS ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (sendHPBeatsSMS_responded ()));
}

void
GrooveService::sendHPBeatsSMS_responded ()
{
  GrooveReply result = getResult ();
}
