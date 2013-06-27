void
GrooveService::popularGetSongs (QString type)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (popularGetSongs_responded ()));
}

void
GrooveService::popularGetSongs_responded ()
{
  GrooveReply result = getResult ();
}
