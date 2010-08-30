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

#ifndef GROOVEPLAYLISTMODEL_H
#define GROOVEPLAYLISTMODEL_H

#include "libgroove_global.h"

#include "groove/songsmodel.h"
class GrooveSong;
class GrooveClient;

#include <memory>

class LIBGROOVESHARED_EXPORT GroovePlaylistModel
  : public GrooveSongsModel
{
  Q_OBJECT

private:
  virtual QVariant data (QModelIndex const &index, int role) const;

public:
  explicit GroovePlaylistModel (std::shared_ptr<GrooveClient> client, QObject *parent);

  /*!
   *  Retrieve a song for a given \a index.
   *
   *  Returns a pointer to the song or 0 if there is an error.
   */
  GrooveSong *select (QModelIndex const &index);

public slots:
  /*!
   *  Appends a given \a song to the end of this playlist.
   *
   *  \sa insert()
   */
  void append (GrooveSong *song);

  /*!
   *  Insert a given \a song at a specified \a position into this playlist.
   */
  void insert (int position, GrooveSong *song);

  /*!
   *  Removes track at a given \a songPosition from this playlist.
   */
  void removeAt (int songPosition);

  /*!
   *  Finds the position of a given \a song in this playlist, searching forward from the index \a from.
   */
  int indexOf (GrooveSong *song, int from = 0);

  GrooveSong *first ();
  GrooveSong *last ();

  /*!
   *  Returns the next track to be played from this playlist, or 0 if there is no next track.
   */
  GrooveSong *next ();

  /*!
   *  Returns the track played previously from this playlist, or 0 if there is no previous track.
   */
  GrooveSong *previous ();

  /*!
   *  Returns the index of the currently playing track.
   */
  int currentTrack () const;

private:
  GrooveSong *songByIndex (QModelIndex const &index) const;

  /*!
   *  Returns the currently playing track on this playlist, or 0 if there is no current track.
   */
  GrooveSong *current () const;

  int m_currentTrack;
  std::shared_ptr<GrooveClient> m_client;
};

#endif /* GROOVEPLAYLISTMODEL_H */
