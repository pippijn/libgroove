void
GrooveService::getArtistAutocomplete (QString const &query)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "query", query },
  };

  request.post (this, SLOT (getArtistAutocomplete_responded ()));
}

void
GrooveService::getArtistAutocomplete_responded ()
{
  QVariantList artists = getResult ()["Artists"];

  QStringList artistList;
  foreach (QVariant const &artist, artists)
    {
      QVariantMap artistData = artist.toMap ();

      artistList.push_back (artistData["Name"].toString ());
    }

  emit getArtistAutocomplete_success (artistList);
}
