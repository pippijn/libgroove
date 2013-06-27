void
GrooveService::logHomepageView ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (logHomepageView_responded ()));
}

void
GrooveService::logHomepageView_responded ()
{
  GrooveReply result = getResult ();
}
