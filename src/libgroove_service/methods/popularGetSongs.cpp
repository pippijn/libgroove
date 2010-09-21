void
GrooveService::popularGetSongs (QString type)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (popularGetSongs_responded ()));
}

void
GrooveService::popularGetSongs_responded ()
{
}
