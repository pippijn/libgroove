void
GrooveService::getContactInfoForFollowers ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getContactInfoForFollowers_responded ()));
}

void
GrooveService::getContactInfoForFollowers_responded ()
{
}
