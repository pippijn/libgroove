/**
 * This method gets the streamKey needed to request the download link to the MP3.
 *
 * Parameters:
 * \param mobile: whether you are using a mobile client or desktop client (true/false).
 *                official client sets this to false but will still work if omitted entirely.
 *                Unknown if a different quality MP3 is retrieved or not.
 * \param prefetch: whether or not the song is being pre-fetched (i.e. downloaded before needed).
 *                  usually safe to set this to false
 * \param songID: the songID of the song you want to download.
 */
void
GrooveService::getStreamKeyFromSongIDEx (bool mobile, bool prefetch, uint songID)
{
  static char const *method = __func__;

  GrooveRequest request (m_client, more (method));

  request << header (method);
  request << map {
    { "parameters", map {
        country (),
        { "mobile", mobile },
        { "prefetch", prefetch },
        { "songID", songID },
      },
    },
  };

  request.post (this, SLOT (getStreamKeyFromSongIDEx_responded ()));
}

void
GrooveService::getStreamKeyFromSongIDEx_responded ()
{
  QVariantMap reply = getReply ();

  QVariantMap result = reply["result"].toMap ();

  QString ip        = result["ip"       ].toString ();
  QString streamKey = result["streamKey"].toString ();

  emit streamKeyReady (ip, streamKey);
}
