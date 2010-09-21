void
GrooveService::unfavorite (uint id, QString what)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (unfavorite_responded ()));
}

void
GrooveService::unfavorite_responded ()
{
}
