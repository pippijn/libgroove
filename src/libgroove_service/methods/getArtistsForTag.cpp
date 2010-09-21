void
GrooveService::getArtistsForTag (TagID tagID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
    { "tagID", uint (tagID) },
  };

  request.post (this, SLOT (getArtistsForTag_responded ()));
}

void
GrooveService::getArtistsForTag_responded ()
{
  QVariantMap reply = getReply ();

  QVariantList result = reply["result"].toList ();

  //emit streamKeyReady (ip, streamKey);
}
