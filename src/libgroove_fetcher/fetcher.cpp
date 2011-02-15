/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "groove/client.h"
#include "groove/data/song.h"
#include "groove/fetcher.h"
#include "groove/service.h"
#include "groove/settings.h"

#include <QDebug>
#include <QDir>
#include <QNetworkReply>

static int
system (QString const &command)
{
  return system (command.toStdString ().c_str ());
}

static void
downloadCover (GrooveSong const &song, QString path)
{
  path += QDir::separator ();
  path += ".art";
  if (GROOVE_VERIFY (QDir ().mkpath (path), "unable to create path to cache: " + path))
    return;

  path += QDir::separator ();
  path += song.coverArtFilename ();

  if (!QFile::exists (path))
    system ("wget -q http://beta.grooveshark.com/static/amazonart/m" + song.coverArtFilename () +
            " -O " + path + "&");
}

static QString
make_cache (GrooveSong const &song)
{
  QString path = Settings.cachedir;

  downloadCover (song, path);

  path += QDir::separator ();
  path += song.artistName ();
  path += QDir::separator ();
  path += song.albumName ();

  LDEBUG << "making cache path: " << path;
  if (GROOVE_VERIFY (QDir ().mkpath (path), "unable to create path to cache: " + path))
    return QString ();

  path += QDir::separator ();
  path += song.songName ();
  path += ".mp3";

  return path;
}


GrooveFetcher::GrooveFetcher (GrooveSong const &song, std::shared_ptr<GrooveClient> client)
  : m_file (make_cache (song))
  , m_nowStreaming (false)
  , m_client (client)
  , m_song ({ song.songName (), song.songID ().toInt () })
{
}

GrooveFetcher::~GrooveFetcher ()
{
}

QString
GrooveFetcher::name () const
{
  return m_song.name;
}

QString
GrooveFetcher::fileName () const
{
  return m_file.fileName ();
}

bool
GrooveFetcher::streaming () const
{
  return m_nowStreaming;
}


void
GrooveFetcher::fetch (GrooveService &service)
{
  if (m_nowStreaming)
    {
      LDEBUG << "Already streaming " << m_song.name << ", ignoring request";
      return;
    }

  if (!m_file.exists ())
    {
      LDEBUG << "Fetching " << m_song.name;

      if (GROOVE_VERIFY (m_file.open (QIODevice::WriteOnly), "could not open output file"))
        return;

      m_nowStreaming = true;

      LDEBUG << "Started streaming for " << m_song.name << " (id: " << m_song.ID << ")";
      /* TODO: error handling */
      connect ( &service
              , SIGNAL (getStreamKeyFromSongIDEx_success (QString, QString))
              , this
              , SLOT (onStreamKeyReady (QString, QString)));
      service.getStreamKeyFromSongIDEx (false, false, m_song.ID);
    }
  else
    emit songReady ();
}

void
GrooveFetcher::onStreamKeyReady (QString ip, QString streamKey)
{
  LDEBUG << "Ready for " << m_song.ID;

  QNetworkRequest req (QUrl ("http://" + ip + "/stream.php"));
  req.setHeader (req.ContentTypeHeader, "application/x-www-form-urlencoded");

  LDEBUG << "Sending request to " << req.url ().toString () << " to start stream";

  streamKey = "streamKey=" + streamKey;
  QNetworkReply *streamingReply = m_client->networkManager ().post (req, streamKey.toAscii ());

  qDebug () << Q_FUNC_INFO << streamingReply->request ().url ();
  qDebug () << Q_FUNC_INFO << streamingReply->rawHeaderList ();

  connect (streamingReply, SIGNAL (error (QNetworkReply::NetworkError)), SLOT (onStreamError ()));
  connect (streamingReply, SIGNAL (readyRead ()), SLOT (onStreamReadReady ()));
  connect (streamingReply, SIGNAL (downloadProgress (qint64, qint64)), SLOT (onStreamProgress (qint64, qint64)));
  connect (streamingReply, SIGNAL (finished ()), SLOT (onStreamingFinished ()));
}

void
GrooveFetcher::onStreamError ()
{
  LDEBUG << "Streaming error: " << qobject_cast<QIODevice *> (sender ())->errorString ();
}

void
GrooveFetcher::onStreamProgress (qint64 bytesReceived, qint64 bytesTotal)
{
  LDEBUG << "downloaded " << bytesReceived << " / " << bytesTotal;
}

void
GrooveFetcher::onStreamReadReady ()
{
  QIODevice *httpStream = qobject_cast<QIODevice *> (sender ());

  if (GROOVE_VERIFY (httpStream, "no stream pointer from sender"))
    return;

  m_file.write (httpStream->readAll ());

#if 0
  LDEBUG << "Stream data length: " << m_file.size ();
#endif
}

void
GrooveFetcher::onStreamingFinished ()
{
  LDEBUG << "finished";

  m_file.close ();

  m_nowStreaming = false;

  emit songReady ();
}
