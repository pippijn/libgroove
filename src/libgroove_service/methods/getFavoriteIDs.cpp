void
GrooveService::getFavoriteIDs (uint userID, QString ofWhat)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getFavoriteIDs_responded ()));
}

void
GrooveService::getFavoriteIDs_responded ()
{
  GrooveReply result = getResult ();
}
