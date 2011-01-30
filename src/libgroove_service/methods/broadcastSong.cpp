void
GrooveService::broadcastSong (QString message, QString link, QString username, QString password, uint songID, QString service, bool saveCredentials)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (broadcastSong_responded ()));
}

void
GrooveService::broadcastSong_responded ()
{
}
