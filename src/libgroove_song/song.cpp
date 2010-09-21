/*
 * Copyright © 2010 Robin Burchell <robin.burchell@collabora.co.uk>
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

#include "groove/client.h"
#include "groove/service.h"
#include "groove/song.h"

#include "groove/private/request.h"

#include <QTime>

#include <qjson/parser.h>

struct GrooveSong::Data
{
  std::shared_ptr<GrooveClient> m_client;
  QVariantMap m_data;
  QAtomicInt m_refCount;
  GrooveService m_service;

  Data (std::shared_ptr<GrooveClient> client, QVariantMap const &data, GrooveSong *song)
    : m_client (client)
    , m_data (data)
    , m_refCount (0)
    , m_service (client, "(null)", song)
  {
  }
};

inline GrooveSong::GrooveSong (std::shared_ptr<GrooveClient> client, QVariantMap const &data)
  : d (new Data (client, data, this))
{
}

GrooveSong::~GrooveSong ()
{
  printf ("bye %p\n", this);
}

inline void
GrooveSong::ref ()
{
  d->m_refCount.ref ();
}

inline void
GrooveSong::deref ()
{
  if (!d->m_refCount.deref ())
    deleteLater ();
}

GrooveSongPointer
GrooveSong::make (std::shared_ptr<GrooveClient> client, QVariantMap const &data)
{
  return new GrooveSong (client, data);
}

QString
GrooveSong::songID () const
{
  return d->m_data["SongID"].toString ();
}

int
GrooveSong::albumID () const
{
  return d->m_data["AlbumID"].toInt ();
}

int
GrooveSong::artistID () const
{
  return d->m_data["ArtistID"].toInt ();
}

int
GrooveSong::genreID () const
{
  return d->m_data["GenreID"].toInt ();
}

QString
GrooveSong::name () const
{
  return d->m_data["Name"].toString ();
}

QString
GrooveSong::songName () const
{
  return d->m_data["SongName"].toString ();
}

QString
GrooveSong::albumName () const
{
  return d->m_data["AlbumName"].toString ();
}

QString
GrooveSong::artistName () const
{
  return d->m_data["ArtistName"].toString ();
}

int
GrooveSong::year () const
{
  return d->m_data["Year"].toInt ();
}

int
GrooveSong::trackNum () const
{
  return d->m_data["TrackNum"].toInt ();
}

QString
GrooveSong::coverArtFilename () const
{
  return d->m_data["CoverArtFilename"].toString ();
}

int
GrooveSong::TSAdded () const
{
  return d->m_data["TSAdded"].toInt ();
}

int
GrooveSong::avgRating () const
{
  return d->m_data["AvgRating"].toInt ();
}

int
GrooveSong::avgDuration () const
{
  return d->m_data["AvgDuration"].toInt ();
}

int
GrooveSong::estimateDuration () const
{
  return d->m_data["EstimateDuration"].toInt ();
}

QString
GrooveSong::avgDurationMins () const
{
  return QTime ().addSecs (avgDuration ()).toString ("m:ss");
}

QString
GrooveSong::estimateDurationMins () const
{
  return QTime ().addSecs (estimateDuration ()).toString ("m:ss");
}

int
GrooveSong::flags () const
{
  return d->m_data["Flags"].toInt ();
}

int
GrooveSong::isLowBitrateAvailable () const
{
  return d->m_data["IsLowBitrateAvailable"].toInt ();
}

int
GrooveSong::songVerified () const
{
  return d->m_data["SongVerified"].toInt ();
}

int
GrooveSong::albumVerified () const
{
  return d->m_data["AlbumVerified"].toInt ();
}

int
GrooveSong::artistVerified () const
{
  return d->m_data["ArtistVerified"].toInt ();
}

int
GrooveSong::popularity () const
{
  return d->m_data["Popularity"].toInt ();
}

int
GrooveSong::albumPopularity () const
{
  return d->m_data["AlbumPopularity"].toInt ();
}

int
GrooveSong::artistPopularity () const
{
  return d->m_data["ArtistPopularity"].toInt ();
}

int
GrooveSong::songPlays () const
{
  return d->m_data["SongPlays"].toInt ();
}

int
GrooveSong::artistPlays () const
{
  return d->m_data["ArtistPlays"].toInt ();
}

int
GrooveSong::songClicks () const
{
  return d->m_data["SongClicks"].toInt ();
}

int
GrooveSong::albumClicks () const
{
  return d->m_data["AlbumClicks"].toInt ();
}

int
GrooveSong::artistClicks () const
{
  return d->m_data["ArtistClicks"].toInt ();
}

int
GrooveSong::querySongClicks () const
{
  return d->m_data["QuerySongClicks"].toInt ();
}

int
GrooveSong::queryAlbumClicks () const
{
  return d->m_data["QueryAlbumClicks"].toInt ();
}

int
GrooveSong::queryArtistClicks () const
{
  return d->m_data["QueryArtistClicks"].toInt ();
}

int
GrooveSong::sphinxWeight () const
{
  return d->m_data["sphinxWeight"].toInt ();
}

int
GrooveSong::score () const
{
  return d->m_data["Score"].toInt ();
}

QString
GrooveSong::DSName () const
{
  return d->m_data["DSName"].toString ();
}

QString
GrooveSong::DALName () const
{
  return d->m_data["DALName"].toString ();
}

QString
GrooveSong::DAName () const
{
  return d->m_data["DAName"].toString ();
}

int
GrooveSong::TSAddedInt () const
{
  return d->m_data["TSAddedInt"].toInt ();
}

int
GrooveSong::rank () const
{
  return d->m_data["Rank"].toInt ();
}

void
GrooveSong::startStreaming ()
{
  llog << DEBUG << LOG_FUNC << "Started streaming for " << songName () << " (id: " << songID () << ")";
  /* TODO: error handling */
  connect (&d->m_service, SIGNAL (streamKeyReady (QString, QString)), this, SLOT (streamKeyReady (QString, QString)));
  d->m_service.getStreamKeyFromSongIDEx (false, false, songID ().toInt ());
}

void
GrooveSong::streamKeyReady (QString ip, QString streamKey)
{
  llog << DEBUG << LOG_FUNC << "Ready for " << songName ();

  QNetworkRequest req (QUrl (GrooveRequest::stream (ip)));
  req.setHeader (req.ContentTypeHeader, "application/x-www-form-urlencoded");

  llog << DEBUG << LOG_FUNC << "Sending request to " << req.url ().toString () << " to start stream";

  streamKey = "streamKey=" + streamKey;
  QNetworkReply *streamingReply = d->m_client->networkManager ().post (req, streamKey.toAscii ());

  emit streamingStarted (streamingReply);
}

void
intrusive_ptr_add_ref (GrooveSong *song)
{
  song->ref ();
}

void
intrusive_ptr_release (GrooveSong *song)
{
  song->deref ();
}
