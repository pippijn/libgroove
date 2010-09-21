void
GrooveService::renamePlaylist (uint playlistID, QString playlistName)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (renamePlaylist_responded ()));
}

void
GrooveService::renamePlaylist_responded ()
{
}
