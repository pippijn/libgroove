#include "fetcher.h"

#include "groove/song.h"

#include <QDebug>
#include <QDir>
#include <QNetworkReply>

static QString
make_cache (GrooveSong const &song)
{
  QString path = "cache";
  path += QDir::separator ();
  path += song.artistName ();
  path += QDir::separator ();
  path += song.albumName ();

  if (GROOVE_VERIFY (QDir ().mkpath (path), "unable to create path to cache"))
    return QString ();

  path += QDir::separator ();
  path += song.songName ();
  path += ".mp3";

  return path;
}


Fetcher::Fetcher (GrooveSong &song)
  : m_file (make_cache (song))
  , m_song (song)
  , m_nowStreaming (false)
{
  m_song.ref ();
}

Fetcher::~Fetcher ()
{
  m_song.deref ();
}

QString
Fetcher::fileName () const
{
  return m_file.fileName ();
}

bool
Fetcher::streaming () const
{
  return m_nowStreaming;
}


void
Fetcher::fetch ()
{
  if (m_nowStreaming)
    {
      qDebug () << Q_FUNC_INFO << "Already streaming " << m_song.songName () << ", ignoring request";
      return;
    }

  if (!m_file.exists ())
    {
      qDebug () << Q_FUNC_INFO << "Fetching " << m_song.songName ();

      if (GROOVE_VERIFY (m_file.open (QIODevice::WriteOnly), "could not open output file"))
        return;

      m_nowStreaming = true;

      connect (&m_song, SIGNAL (streamingStarted (QNetworkReply *)), SLOT (onStreamingStarted (QNetworkReply *)));
      m_song.startStreaming ();
    }
  else
    emit songReady ();
}

void
Fetcher::onStreamingStarted (QNetworkReply *httpStream)
{
  qDebug () << Q_FUNC_INFO << "Streaming started... :)";

  connect (httpStream, SIGNAL (readyRead ()), SLOT (onStreamReadReady ()));
  connect (httpStream, SIGNAL (finished ()), SLOT (onStreamingFinished ()));
}

void
Fetcher::onStreamReadReady ()
{
  QIODevice *httpStream = qobject_cast<QIODevice *> (sender ());

  if (GROOVE_VERIFY (httpStream, "no stream pointer from sender"))
    return;

  m_file.write (httpStream->readAll ());

  qDebug () << Q_FUNC_INFO << "Stream data length: " << m_file.size ();
}

void
Fetcher::onStreamingFinished ()
{
  qDebug () << Q_FUNC_INFO << "finished";

  m_file.close ();

  m_nowStreaming = false;

  emit songReady ();
}
