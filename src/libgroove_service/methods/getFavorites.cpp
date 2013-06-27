void
GrooveService::getFavorites (uint userID, QString ofWhat)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getFavorites_responded ()));
}

void
GrooveService::getFavorites_responded ()
{
  GrooveReply result = getResult ();
}
