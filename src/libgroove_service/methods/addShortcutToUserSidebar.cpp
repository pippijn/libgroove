void
GrooveService::addShortcutToUserSidebar ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (addShortcutToUserSidebar_responded ()));
}

void
GrooveService::addShortcutToUserSidebar_responded ()
{
  GrooveReply result = getResult ();
}
