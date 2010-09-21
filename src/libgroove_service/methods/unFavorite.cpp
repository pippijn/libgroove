void
GrooveService::unFavorite (uint id, QString what)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (unFavorite_responded ()));
}

void
GrooveService::unFavorite_responded ()
{
}
