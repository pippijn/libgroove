void
GrooveService::changePrivacySettings ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (changePrivacySettings_responded ()));
}

void
GrooveService::changePrivacySettings_responded ()
{
  GrooveReply result = getResult ();
}
