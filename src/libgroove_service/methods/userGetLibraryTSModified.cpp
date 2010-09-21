void
GrooveService::userGetLibraryTSModified ()
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request.parameters () << map {
      { "XXX", "XXX" },
  };

  request.post (this, SLOT (userGetLibraryTSModified_responded ()));
}

void
GrooveService::userGetLibraryTSModified_responded ()
{
}
