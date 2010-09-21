void
GrooveService::createWidgetIDFromSongIDs (QList<uint> songIDs)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (createWidgetIDFromSongIDs_responded ()));
}

void
GrooveService::createWidgetIDFromSongIDs_responded ()
{
}
