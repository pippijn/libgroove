void
GrooveService::getThumbplayRingtoneSearchResults ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getThumbplayRingtoneSearchResults_responded ()));
}

void
GrooveService::getThumbplayRingtoneSearchResults_responded ()
{
  GrooveReply result = getResult ();
}
