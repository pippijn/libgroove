void
GrooveService::getCombinedFeedData (uint loggedInUserID, QDate day, QList<uint> userIDs)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getCombinedFeedData_responded ()));
}

void
GrooveService::getCombinedFeedData_responded ()
{
  GrooveReply result = getResult ();
}
