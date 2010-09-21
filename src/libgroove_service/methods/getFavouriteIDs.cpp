void
GrooveService::getFavouriteIDs (uint userID, QString ofWhat)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (getFavouriteIDs_responded ()));
}

void
GrooveService::getFavouriteIDs_responded ()
{
}
