void
GrooveService::getAffiliateDownloadURLs (QString songName, QString artistName)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, service, method);

  request.parameters () << map {
    { "XXX", "XXX" },
  };

  request.post (this, SLOT (getAffiliateDownloadURLs_responded ()));
}

void
GrooveService::getAffiliateDownloadURLs_responded ()
{
}
