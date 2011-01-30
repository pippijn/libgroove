void
GrooveService::getUserSidebar ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getUserSidebar_responded ()));
}

void
GrooveService::getUserSidebar_responded ()
{
}
