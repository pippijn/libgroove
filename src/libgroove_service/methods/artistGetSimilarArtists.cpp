void
GrooveService::artistGetSimilarArtists (uint artistID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (artistGetSimilarArtists_responded ()));
}

void
GrooveService::artistGetSimilarArtists_responded ()
{
  GrooveReply result = getResult ();
}
