/**
 * This method searches for a song using a provided search term
 *
 * Parameters:
 * \param query: the search query
 * \param type: the search type (types are 'Songs', 'Artists', 'Albums' or 'Playlists')
 */
void
GrooveService::getSearchResults (QString query, QString type)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "query", query },
    { "type", type },
  };

  request.post (this, SLOT (getSearchResults_responded ()));
}

void
GrooveService::getSearchResults_responded ()
{
  QVariantList songs = getResult ()["Songs"];

  QList<GrooveSongPointer> songList;
  foreach (QVariant const &song, songs)
    {
      QVariantMap songData = song.toMap ();

      songList.push_back (GrooveSong::make (songData));
    }

  emit searchResultsReady (songList);
}
