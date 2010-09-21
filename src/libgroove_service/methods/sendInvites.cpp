void
GrooveService::sendInvites ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (sendInvites_responded ()));
}

void
GrooveService::sendInvites_responded ()
{
}
