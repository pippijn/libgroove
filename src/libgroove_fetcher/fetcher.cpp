/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "groove/fetcher.h"
#include "groove/settings.h"
#include "groove/song.h"

#include <QDir>
#include <QNetworkReply>
#include <QSettings>

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
            " -O " + path);
}

static QString
make_cache (GrooveSong const &song)
{
  QString path = QSettings ().value (GrooveSettings::CACHEDIR, "cache").toString ();

  downloadCover (song, path);

  path += QDir::separator ();
  path += song.artistName ();
  path += QDir::separator ();
  path += song.albumName ();

  llog << DEBUG << "making cache path: " << path;
  if (GROOVE_VERIFY (QDir ().mkpath (path), "unable to create path to cache: " + path))
    return QString ();

  path += QDir::separator ();
  path += song.songName ();
  path += ".mp3";

  return path;
}


GrooveFetcher::GrooveFetcher (GrooveSongPointer song)
  : m_file (make_cache (*song))
  , m_song (song)
  , m_nowStreaming (false)
{
}

GrooveFetcher::~GrooveFetcher ()
{
}

QString
GrooveFetcher::name () const
{
  return m_song->songName ();
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
GrooveFetcher::fetch ()
{
  if (m_nowStreaming)
    {
      llog << DEBUG << "Already streaming " << m_song->songName () << ", ignoring request";
      return;
    }

  if (!m_file.exists ())
    {
      llog << DEBUG << "Fetching " << m_song->songName ();

      if (GROOVE_VERIFY (m_file.open (QIODevice::WriteOnly), "could not open output file"))
        return;

      m_nowStreaming = true;

      connect (m_song.get (), SIGNAL (streamingStarted (QNetworkReply *)), SLOT (onStreamingStarted (QNetworkReply *)));
      m_song->startStreaming ();
    }
  else
    emit songReady ();
}

void
GrooveFetcher::onStreamingStarted (QNetworkReply *httpStream)
{
  llog << DEBUG << "Streaming started";

  connect (httpStream, SIGNAL (readyRead ()), SLOT (onStreamReadReady ()));
  connect (httpStream, SIGNAL (finished ()), SLOT (onStreamingFinished ()));
}

void
GrooveFetcher::onStreamReadReady ()
{
  QIODevice *httpStream = qobject_cast<QIODevice *> (sender ());

  if (GROOVE_VERIFY (httpStream, "no stream pointer from sender"))
    return;

  m_file.write (httpStream->readAll ());

#if 0
  llog << DEBUG << "Stream data length: " << m_file.size ();
#endif
}

void
GrooveFetcher::onStreamingFinished ()
{
  llog << DEBUG << "finished";

  m_file.close ();

  m_nowStreaming = false;

  emit songReady ();
}
