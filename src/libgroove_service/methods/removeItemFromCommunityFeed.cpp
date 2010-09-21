void
GrooveService::removeItemFromCommunityFeed ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (removeItemFromCommunityFeed_responded ()));
}

void
GrooveService::removeItemFromCommunityFeed_responded ()
{
}
