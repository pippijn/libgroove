void
GrooveService::logoutUser ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request << map {
    { "parameters", "service.php" },
  };

  //request.post (this, SLOT (logoutUser_responded ()));
  request.post (parent (), m_slot);
}

void
GrooveService::logoutUser_responded ()
{
}
