void
GrooveService::logThemeOutboundLinkClick ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (logThemeOutboundLinkClick_responded ()));
}

void
GrooveService::logThemeOutboundLinkClick_responded ()
{
  GrooveReply result = getResult ();
}
