void
GrooveService::getSearchSuggestion ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getSearchSuggestion_responded ()));
}

void
GrooveService::getSearchSuggestion_responded ()
{
  GrooveReply result = getResult ();
}
