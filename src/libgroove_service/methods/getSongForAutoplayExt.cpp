void
GrooveService::getSongForAutoplayExt ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getSongForAutoplayExt_responded ()));
}

void
GrooveService::getSongForAutoplayExt_responded ()
{
  GrooveReply result = getResult ();
}
