void
GrooveService::getGoogleContacts ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getGoogleContacts_responded ()));
}

void
GrooveService::getGoogleContacts_responded ()
{
  GrooveReply result = getResult ();
}
