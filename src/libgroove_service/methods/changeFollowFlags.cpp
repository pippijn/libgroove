void
GrooveService::changeFollowFlags ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (changeFollowFlags_responded ()));
}

void
GrooveService::changeFollowFlags_responded ()
{
}
