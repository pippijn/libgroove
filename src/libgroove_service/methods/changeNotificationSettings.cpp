void
GrooveService::changeNotificationSettings ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (changeNotificationSettings_responded ()));
}

void
GrooveService::changeNotificationSettings_responded ()
{
}
