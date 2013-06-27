void
GrooveService::initiateQueueEx ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters ();

  request.post (this, SLOT (playlistGetSongs_responded ()));
}

void
GrooveService::initiateQueueEx_responded ()
{
  QString queueID = getResult ();
}
