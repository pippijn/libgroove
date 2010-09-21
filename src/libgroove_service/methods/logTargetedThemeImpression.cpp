void
GrooveService::logTargetedThemeImpression ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (logTargetedThemeImpression_responded ()));
}

void
GrooveService::logTargetedThemeImpression_responded ()
{
}
