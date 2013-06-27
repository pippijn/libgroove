void
GrooveService::getCombinedProcessedFeedData ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getCombinedProcessedFeedData_responded ()));
}

void
GrooveService::getCombinedProcessedFeedData_responded ()
{
  GrooveReply result = getResult ();
}
