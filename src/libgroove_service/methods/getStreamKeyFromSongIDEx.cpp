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

  GrooveRequest request (m_client, more, method, "jsqueue");

  request.parameters () << map {
    { "mobile",   mobile },
    { "prefetch", prefetch },
    { "songID",   songID },
  };

  request.post (this, SLOT (getStreamKeyFromSongIDEx_responded ()));
}

/**
 * Response:
 * \param streamKey: a 20-character hex string to POST to the server specified in streamServer
 * \param ip: the server to POST to. (this used to be called streamServer)
 * \param streamServerID: unknown, integer.
 * \param uSecs: the time, in microseconds, which the streamkey will be active for.
 * \param filetoken: same as getTokenForSong
 */
void
GrooveService::getStreamKeyFromSongIDEx_responded ()
{
  GrooveReply result = getResult ();

  QString streamKey      = result["streamKey"     ];
  QString ip             = result["ip"            ];
  int     streamServerID = result["streamServerID"];
  QString FileToken      = result["FileToken"     ];
  int     uSecs          = result["uSecs"         ];

  LDEBUG << "got streamKey=" << streamKey << ", ip=" << ip;
  GROOVE_VERIFY_OR_DIE (!streamKey.isEmpty (), "got invalid streamKey from server");
  GROOVE_VERIFY_OR_DIE (!ip.isEmpty (), "got invalid streaming IP from server");

  emit getStreamKeyFromSongIDEx_success (ip, streamKey);
}
