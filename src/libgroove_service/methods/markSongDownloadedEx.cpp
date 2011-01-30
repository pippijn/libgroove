void
GrooveService::markSongDownloadedEx (uint streamServerID, QString streamKey, uint songID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "streamKey", streamKey },
    { "streamServerID", streamServerID },
    { "songID", songID },
  };

  request.post (this, SLOT (playlistGetSongs_responded ()));
}

void
GrooveService::markSongDownloadedEx_responded ()
{
}
