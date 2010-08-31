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

#include "grooveplaylistmodel.h"
#include "groove/settings.h"
#include "groove/song.h"

#include <QSettings>

#include <algorithm>

GroovePlaylistModel::GroovePlaylistModel (std::shared_ptr<GrooveClient> client, QObject *parent)
  : GrooveSongsModel (GrooveSettings::section::PLAYLIST, parent)
  , m_client (client)
  , m_currentTrack (-1)
{
}

GrooveSongPointer
GroovePlaylistModel::songByIndex (QModelIndex const &index) const
{
  //qDebug () << index.row ();
  if (GROOVE_VERIFY (index.row () >= 0, "row is negative"))
    return NULL;
  if (GROOVE_VERIFY (index.row () < m_songs.count (), "row is higher than the number of songs model contains"))
    return NULL;

  return m_songs[index.row ()];
}

void
GroovePlaylistModel::append (GrooveSongPointer song)
{
  if (GROOVE_VERIFY (song, "song is NULL"))
    return;

  insert (m_songs.count (), song);
}

void
GroovePlaylistModel::insert (int position, GrooveSongPointer song)
{
  if (GROOVE_VERIFY (song, "song is NULL"))
    return;
  if (GROOVE_VERIFY (position >= 0, "position is less than 0"))
    return;
  if (GROOVE_VERIFY (position <= m_songs.count (), "position is greater than it should be"))
    return;

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
  m_songs.removeAt (songPosition);
  endRemoveRows ();
}

int
GroovePlaylistModel::indexOf (GrooveSongPointer song, int from)
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

GrooveSongPointer
GroovePlaylistModel::current () const
{
  if (currentTrack () >= count () || currentTrack () < 0 || !count ())
    return NULL;

  return m_songs.at (currentTrack ());
}

GrooveSongPointer
GroovePlaylistModel::select (QModelIndex const &index)
{
  GrooveSongPointer song = songByIndex (index);

  if (!song)
    return NULL;

  m_currentTrack = index.row () - 1;

  return next ();
}

GrooveSongPointer
GroovePlaylistModel::first ()
{
  m_currentTrack = -1;

  return next ();
}

GrooveSongPointer
GroovePlaylistModel::last ()
{
  m_currentTrack = count ();

  return previous ();
}

GrooveSongPointer
GroovePlaylistModel::next ()
{
  if (++m_currentTrack >= count ())
    {
      m_currentTrack = count () - 1;
      qDebug () << Q_FUNC_INFO << "end of playlist reached, current track =" << m_currentTrack;
      return NULL;
    }

  qDebug () << Q_FUNC_INFO << "reading next track, current track =" << m_currentTrack
                           << "(" << current ()->songName () << ")";

  return current ();
}

GrooveSongPointer
GroovePlaylistModel::previous ()
{
  if (--m_currentTrack < 0 || !count ())
    {
      m_currentTrack = 0;
      qDebug () << Q_FUNC_INFO << "beginning of playlist reached, current track =" << m_currentTrack;
      return NULL;
    }

  qDebug () << Q_FUNC_INFO << "reading next track, current track =" << m_currentTrack
                           << "(" << current ()->songName () << ")";

  return current ();
}

int
GroovePlaylistModel::currentTrack () const
{
  return m_currentTrack;
}

QVariant
GroovePlaylistModel::data (QModelIndex const &index, int role) const
{
  QVariant data = GrooveSongsModel::data (index, role);

  GrooveSongPointer song = m_songs[index.row ()];

  switch (role)
    {
    case Qt::ToolTipRole:
      if (m_visible[index.column ()] == "albumName")
        return QString ("<img src='%1/.art/%2'/>")
               .arg (QSettings ().value (GrooveSettings::CACHEDIR, "cache").toString ())
               .arg (song->coverArtFilename ())
               ;
    }

  return data;
}
