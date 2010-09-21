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

#ifndef GROOVESONG_H
#define GROOVESONG_H

#include "libgroove_global.h"

#include "groove/songptr.h"

#include <QMetaType>
#include <QSharedData>
#include <QSharedDataPointer>
#include <QString>
#include <QVariantMap>
class QNetworkReply;

#include <memory>

class LIBGROOVESHARED_EXPORT GrooveSong
  : public QObject
{
  Q_OBJECT

  friend void intrusive_ptr_add_ref (GrooveSong *song);
  friend void intrusive_ptr_release (GrooveSong *song);

  GrooveSong (QVariantMap const &data);
  ~GrooveSong ();

  void ref ();
  void deref ();

public:
  static GrooveSongPointer make (QVariantMap const &data);

  Q_PROPERTY (QString songID READ songID)                               QString songID () const;
  Q_PROPERTY (int albumID READ albumID)                                 int albumID () const;
  Q_PROPERTY (int artistID READ artistID)                               int artistID () const;
  Q_PROPERTY (int genreID READ genreID)                                 int genreID () const;
  Q_PROPERTY (QString name READ name)                                   QString name () const;
  Q_PROPERTY (QString songName READ songName)                           QString songName () const;
  Q_PROPERTY (QString albumName READ albumName)                         QString albumName () const;
  Q_PROPERTY (QString artistName READ artistName)                       QString artistName () const;
  Q_PROPERTY (int year READ year)                                       int year () const;
  Q_PROPERTY (int trackNum READ trackNum)                               int trackNum () const;
  Q_PROPERTY (QString coverArtFilename READ coverArtFilename)           QString coverArtFilename () const;
  Q_PROPERTY (int TSAdded READ TSAdded)                                 int TSAdded () const;
  Q_PROPERTY (int avgRating READ avgRating)                             int avgRating () const;
  Q_PROPERTY (int avgDuration READ avgDuration)                         int avgDuration () const;
  Q_PROPERTY (int estimateDuration READ estimateDuration)               int estimateDuration () const;
  Q_PROPERTY (QString avgDurationMins READ avgDurationMins)             QString avgDurationMins () const;
  Q_PROPERTY (QString estimateDurationMins READ estimateDurationMins)   QString estimateDurationMins () const;
  Q_PROPERTY (int flags READ flags)                                     int flags () const;
  Q_PROPERTY (int isLowBitrateAvailable READ isLowBitrateAvailable)     int isLowBitrateAvailable () const;
  Q_PROPERTY (int songVerified READ songVerified)                       int songVerified () const;
  Q_PROPERTY (int albumVerified READ albumVerified)                     int albumVerified () const;
  Q_PROPERTY (int artistVerified READ artistVerified)                   int artistVerified () const;
  Q_PROPERTY (int popularity READ popularity)                           int popularity () const;
  Q_PROPERTY (int albumPopularity READ albumPopularity)                 int albumPopularity () const;
  Q_PROPERTY (int artistPopularity READ artistPopularity)               int artistPopularity () const;
  Q_PROPERTY (int songPlays READ songPlays)                             int songPlays () const;
  Q_PROPERTY (int artistPlays READ artistPlays)                         int artistPlays () const;
  Q_PROPERTY (int songClicks READ songClicks)                           int songClicks () const;
  Q_PROPERTY (int albumClicks READ albumClicks)                         int albumClicks () const;
  Q_PROPERTY (int artistClicks READ artistClicks)                       int artistClicks () const;
  Q_PROPERTY (int querySongClicks READ querySongClicks)                 int querySongClicks () const;
  Q_PROPERTY (int queryAlbumClicks READ queryAlbumClicks)               int queryAlbumClicks () const;
  Q_PROPERTY (int queryArtistClicks READ queryArtistClicks)             int queryArtistClicks () const;
  Q_PROPERTY (int sphinxWeight READ sphinxWeight)                       int sphinxWeight () const;
  Q_PROPERTY (int score READ score)                                     int score () const;
  Q_PROPERTY (QString DSName READ DSName)                               QString DSName () const;
  Q_PROPERTY (QString DALName READ DALName)                             QString DALName () const;
  Q_PROPERTY (QString DAName READ DAName)                               QString DAName () const;
  Q_PROPERTY (int TSAddedInt READ TSAddedInt)                           int TSAddedInt () const;
  Q_PROPERTY (int rank READ rank)                                       int rank () const;

private:
  struct Data;
  std::auto_ptr<Data> d;
};

#endif /* GROOVESONG_H */
