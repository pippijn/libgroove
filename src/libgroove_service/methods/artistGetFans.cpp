void
GrooveService::artistGetFans (uint offset, uint artistID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (artistGetFans_responded ()));
}

void
GrooveService::artistGetFans_responded ()
{
  GrooveReply result = getResult ();
}
