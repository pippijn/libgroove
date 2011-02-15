void
GrooveService::logoutUser ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << "service.php";

  request.post (this, SLOT (logoutUser_responded ()));
}

void
GrooveService::logoutUser_responded ()
{
  GrooveReply result = getResult ();
}
