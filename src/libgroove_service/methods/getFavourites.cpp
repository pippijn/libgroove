void
GrooveService::getFavourites (uint userID, QString ofWhat)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (getFavourites_responded ()));
}

void
GrooveService::getFavourites_responded ()
{
}
