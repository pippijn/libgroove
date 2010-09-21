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

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
    { "type", type },
    { "query", query },
  };

  //request.post (this, SLOT (getSearchResults_responded ()));
  request.post (parent (), m_slot);
}

void
GrooveService::getSearchResults_responded ()
{
}
