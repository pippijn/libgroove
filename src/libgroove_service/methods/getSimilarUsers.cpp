void
GrooveService::getSimilarUsers ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getSimilarUsers_responded ()));
}

void
GrooveService::getSimilarUsers_responded ()
{
}
