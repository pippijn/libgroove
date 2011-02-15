/**
 * This method searches for a song using a provided search term.
 *
 * Parameters:
 * \param query: the search query
 * \param types: a list of search types (types are 'Songs', 'Artists', 'Albums' or 'Playlists')
 */
void
GrooveService::getSearchResultsEx (QString query, QList<QString> types)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "query", query },
    { "type", types },
  };

  request.post (this, SLOT (getSearchResultsEx_responded ()));
}

void
GrooveService::getSearchResultsEx_responded ()
{
  QVariantList songs = getResult ()["result"]["Songs"];

  QList<GrooveSongPointer> songList;
  foreach (QVariant const &song, songs)
    {
      QVariantMap songData = song.toMap ();

      songList.push_back (GrooveSong::make (songData));
    }

  emit searchResultsReady (songList);
}
