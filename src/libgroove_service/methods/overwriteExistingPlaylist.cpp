void
GrooveService::overwriteExistingPlaylist (uint playlistID, QList<uint> songIDs)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (overwriteExistingPlaylist_responded ()));
}

void
GrooveService::overwriteExistingPlaylist_responded ()
{
}
