void
GrooveService::getUserByInviteID ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getUserByInviteID_responded ()));
}

void
GrooveService::getUserByInviteID_responded ()
{
  GrooveReply result = getResult ();
}
