void
GrooveService::artistGetSongs (uint offset, uint artistID, bool isVerified)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (artistGetSongs_responded ()));
}

void
GrooveService::artistGetSongs_responded ()
{
}
