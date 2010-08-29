/*
 * Copyright © 2010 Pippijn van Steenhoven <pippijn@xinutec.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "groove/fetcher.h"
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


GrooveFetcher::GrooveFetcher (GrooveSong &song)
  : m_file (make_cache (song))
  , m_song (song)
  , m_nowStreaming (false)
{
  m_song.ref ();
}

GrooveFetcher::~GrooveFetcher ()
{
  m_song.deref ();
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
GrooveFetcher::onStreamingStarted (QNetworkReply *httpStream)
{
  qDebug () << Q_FUNC_INFO << "Streaming started... :)";

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

  qDebug () << Q_FUNC_INFO << "Stream data length: " << m_file.size ();
}

void
GrooveFetcher::onStreamingFinished ()
{
  qDebug () << Q_FUNC_INFO << "finished";

  m_file.close ();

  m_nowStreaming = false;

  emit songReady ();
}
