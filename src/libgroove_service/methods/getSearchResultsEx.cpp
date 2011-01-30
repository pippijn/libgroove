void
GrooveService::getSearchResultsEx ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getSearchResultsEx_responded ()));
}

void
GrooveService::getSearchResultsEx_responded ()
{
}
