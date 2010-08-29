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

#include <algorithm>

#include "grooveplaylistmodel.h"
#include "groove/settings.h"
#include "groove/song.h"

#if 0
#include <QColor>
#endif

GroovePlaylistModel::GroovePlaylistModel (GrooveClient &client, QObject *parent)
  : GrooveSongsModel (GrooveSettings::section::PLAYLIST, parent)
  , m_client (client)
  , m_currentTrack (-1)
{
}

GrooveSong *
GroovePlaylistModel::select (const QModelIndex &index)
{
  GrooveSong *song = songByIndex (index);

  if (!song)
    return 0;

  m_currentTrack = index.row () - 1;

  return next ();
}

GrooveSong *
GroovePlaylistModel::songByIndex (const QModelIndex &index) const
{
  //qDebug () << index.row ();
  if (GROOVE_VERIFY (index.row () >= 0, "row is negative"))
    return 0;
  if (GROOVE_VERIFY (index.row () < m_songs.count (), "row is higher than the number of songs model contains"))
    return 0;

  return m_songs[index.row ()];
}

void
GroovePlaylistModel::append (GrooveSong *song)
{
  if (GROOVE_VERIFY (song, "song is NULL"))
    return;

  /* ref is made inside insert() */
  insert (m_songs.count (), song);
}

void
GroovePlaylistModel::insert (int position, GrooveSong *song)
{
  if (GROOVE_VERIFY (song, "song is NULL"))
    return;
  if (GROOVE_VERIFY (position >= 0, "position is less than 0"))
    return;
  if (GROOVE_VERIFY (position <= m_songs.count (), "position is greater than it should be"))
    return;

  /* acquire a ref */
  song->ref ();

  beginInsertRows (QModelIndex (), position, position);
  m_songs.insert (position, song);
  endInsertRows ();
}

void
GroovePlaylistModel::removeAt (int songPosition)
{
  if (GROOVE_VERIFY (songPosition >= 0, "songPosition is less than 0"))
    return;
  if (GROOVE_VERIFY (songPosition < m_songs.count (), "songPosition is greater than the number of songs"))
    return;

  beginRemoveRows (QModelIndex (), songPosition, songPosition);
  m_songs.at (songPosition)->deref ();
  m_songs.removeAt (songPosition);
  endRemoveRows ();
}

int
GroovePlaylistModel::indexOf (GrooveSong *song, int from)
{
  if (GROOVE_VERIFY (song, "song is NULL"))
    return -1;
  if (GROOVE_VERIFY (from >= 0, "from is negative"))
    return -1;
  if (GROOVE_VERIFY (from <= m_songs.count (), "from is higher than the playlist length"))
    return -1;

#if 0
  for (int i = from; i != m_songs.count (); ++i)
    if (m_songs.at (i) == song)
      return i;
#else
  auto found = std::find (m_songs.begin (), m_songs.end (), song);
  if (found != m_songs.end ())
    return found - m_songs.begin ();
#endif

  return -1;
}

GrooveSong *
GroovePlaylistModel::selectFirst ()
{
  m_currentTrack = -1;
  return next ();
}

GrooveSong *
GroovePlaylistModel::selectLast ()
{
  m_currentTrack = count ();
  return previous ();
}

GrooveSong *
GroovePlaylistModel::current () const
{
  if (currentTrack () >= count () || currentTrack () < 0 || !count ())
    return 0;

  return m_songs.at (currentTrack ());
}

GrooveSong *
GroovePlaylistModel::next ()
{
  if (++m_currentTrack >= count ())
    {
      m_currentTrack = count () - 1;
      return 0;
    }

  emit layoutChanged (); // new colour for active track
  return current ();
}

GrooveSong *
GroovePlaylistModel::previous ()
{
  if (--m_currentTrack < 0 || !count ())
    {
      m_currentTrack = 0;
      return 0;
    }

  emit layoutChanged (); // new colour for active track
  return current ();
}

int
GroovePlaylistModel::currentTrack () const
{
  return m_currentTrack;
}

QVariant
GroovePlaylistModel::data (const QModelIndex &index, int role) const
{
  QVariant data = GrooveSongsModel::data (index, role);

  switch (role)
    {
#if 0
    case Qt::BackgroundColorRole:
      if (songByIndex (index) == current ())
        return QColor (Qt::green);
#endif
    }

  return data;
}
