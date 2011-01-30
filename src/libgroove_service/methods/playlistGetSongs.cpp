void
GrooveService::playlistGetSongs (uint playlistID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "playlistID", playlistID },
  };

  request.post (this, SLOT (playlistGetSongs_responded ()));
}

void
GrooveService::playlistGetSongs_responded ()
{
  QVariantMap result = getResult ();

  QVariantList Songs = result["Songs"].toList ();

  //emit streamKeyReady (ip, streamKey);
}
