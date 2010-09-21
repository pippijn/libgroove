void
GrooveService::songGetFans ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (songGetFans_responded ()));
}

void
GrooveService::songGetFans_responded ()
{
}
