/*
 * Copyright (C) 2010 Robin Burchell <robin.burchell@collabora.co.uk>
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

#include "groovesongsmodel.h"
class GrooveSong;

class GroovePlaylistModel
  : public GrooveSongsModel
{
  Q_OBJECT

public:
  explicit GroovePlaylistModel (QObject *parent = 0);

  /*!
   *  Retrieve a song for a given \a index.
   *
   *  Returns a pointer to the song or 0 if there is an error.
   */
  GrooveSong *select (const QModelIndex &index);

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

  /*!
   *  Resets the playlist index to 0 and returns the first song.
   */
  GrooveSong *selectFirst ();

  /*!
   *  Resets the playlist index to count () and returns the last song.
   */
  GrooveSong *selectLast ();

  /*!
   *  Returns the currently playing track on this playlist, or 0 if there is no current track.
   */
  GrooveSong *current () const;

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
  int currentTrack ();

private:
  GrooveSong *songByIndex (const QModelIndex &index) const;

  int m_currentTrack;
};

#endif /* GROOVEPLAYLISTMODEL_H */
