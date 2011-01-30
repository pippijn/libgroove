void
GrooveService::getContactInfoForFollowedUsers ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getContactInfoForFollowedUsers_responded ()));
}

void
GrooveService::getContactInfoForFollowedUsers_responded ()
{
}
