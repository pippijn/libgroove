void
GrooveService::getServiceStatus ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (getServiceStatus_responded ()));
}

void
GrooveService::getServiceStatus_responded ()
{
}
