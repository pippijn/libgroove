void
GrooveService::doHPBeatsUpgrade ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (doHPBeatsUpgrade_responded ()));
}

void
GrooveService::doHPBeatsUpgrade_responded ()
{
}
