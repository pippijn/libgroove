void
GrooveService::sendMobileAppSMS ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (sendMobileAppSMS_responded ()));
}

void
GrooveService::sendMobileAppSMS_responded ()
{
}
