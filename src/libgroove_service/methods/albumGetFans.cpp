void
GrooveService::albumGetFans ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (albumGetFans_responded ()));
}

void
GrooveService::albumGetFans_responded ()
{
}
