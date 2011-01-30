void
GrooveService::removeShortcutFromUserSidebar ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (removeShortcutFromUserSidebar_responded ()));
}

void
GrooveService::removeShortcutFromUserSidebar_responded ()
{
}
