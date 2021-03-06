void
GrooveService::getRecentlyActiveUsers ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getRecentlyActiveUsers_responded ()));
}

void
GrooveService::getRecentlyActiveUsers_responded ()
{
  GrooveReply result = getResult ();
}
