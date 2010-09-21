void
GrooveService::sendShare ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (sendShare_responded ()));
}

void
GrooveService::sendShare_responded ()
{
}
