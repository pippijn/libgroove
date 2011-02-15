void
GrooveService::getArtistAutocomplete (QString const &query)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "query", query },
  };

  request.post (this, SLOT (getArtistAutocomplete_responded ()));
}

void
GrooveService::getArtistAutocomplete_responded ()
{
  GrooveReply result = getResult ();
}
