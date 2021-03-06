/**
 * This method searches for a song using a provided search term.
 *
 * Parameters:
 * \param query: the search query
 * \param types: a list of search types (types are 'Songs', 'Artists', 'Albums' or 'Playlists')
 */
void
GrooveService::getSearchResultsEx (QString query, QStringList types)
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
  GrooveReply result = getResult ();
  QVariantList songs = result["Songs"];

  // TODO: wtf is going on here? I get any of these three API responses
  if (songs.isEmpty ())
    songs = result["result"];
  if (songs.isEmpty ())
    songs = result["result"]["Songs"];

  QList<GrooveSongPointer> songList;
  foreach (QVariant const &song, songs)
    {
      QVariantMap songData = song.toMap ();

      songList.push_back (GrooveSong::make (songData));
    }

  emit getSearchResultsEx_success (songList);
}
