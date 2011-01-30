void
GrooveService::getArtistAutocomplete ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getArtistAutocomplete_responded ()));
}

void
GrooveService::getArtistAutocomplete_responded ()
{
}
