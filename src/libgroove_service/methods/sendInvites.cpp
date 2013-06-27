void
GrooveService::sendInvites ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (sendInvites_responded ()));
}

void
GrooveService::sendInvites_responded ()
{
  GrooveReply result = getResult ();
}
