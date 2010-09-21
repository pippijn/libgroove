void
GrooveService::getStationByID ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (getStationByID_responded ()));
}

void
GrooveService::getStationByID_responded ()
{
}
