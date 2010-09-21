void
GrooveService::getSongForAutoplayExt ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service (method));

  request << header (method);
  request.parameters () << map {
     { "XXX", "XXX" },
  };

  request.post (this, SLOT (getSongForAutoplayExt_responded ()));
}

void
GrooveService::getSongForAutoplayExt_responded ()
{
}
