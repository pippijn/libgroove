void
GrooveService::getArtistsForTag (TagID tagID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "tagID", uint (tagID) },
  };

  request.post (this, SLOT (getArtistsForTag_responded ()));
}

void
GrooveService::getArtistsForTag_responded ()
{
  QVariantList result = getResult ();

  //emit streamKeyReady (ip, streamKey);
}
