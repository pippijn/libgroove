void
GrooveService::getProcessedUserFeedData ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getProcessedUserFeedData_responded ()));
}

void
GrooveService::getProcessedUserFeedData_responded ()
{
  GrooveReply result = getResult ();
}
