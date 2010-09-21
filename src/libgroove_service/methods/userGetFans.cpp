void
GrooveService::userGetFans ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (userGetFans_responded ()));
}

void
GrooveService::userGetFans_responded ()
{
}
