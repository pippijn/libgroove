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

#include "groove/song.h"
#include "groove/songsmodel.h"

#include <QSettings>
#include <QTime>

#include <map>

static std::map<QString, char const *> propNames = {
  { "songName",         "Title"         },
  { "albumName",        "Album"         },
  { "artistName",       "Artist"        },
  { "year",             "Year"          },
  { "trackNum",         "Track"         },
  { "estimateDuration", "Duration"      },
  { "popularity",       "Popularity"    },
  { "songPlays",        "Plays"         },
  { "songClicks",       "Clicks"        },
  { "score",            "Score"         },
  { "rank",             "Rank"          },
};

GrooveSongsModel::GrooveSongsModel (QString const &modelName, QObject *parent)
  : QAbstractItemModel (parent)
{
  QSettings settings;
  settings.beginGroup (modelName);
  if (!settings.contains ("columns"))
    {
      m_visible.append ("songName");
      m_visible.append ("albumName");
      m_visible.append ("artistName");
      m_visible.append ("estimateDuration");

      settings.setValue ("columns", m_visible);
    }
  else
    {
      GROOVE_VERIFY_OR_DIE (settings.value ("columns").canConvert<QStringList> (),
                            "invalid configuration data for `columns' key");

      m_visible = settings.value ("columns").toStringList ();
    }

  settings.endGroup ();
}

GrooveSongsModel::~GrooveSongsModel ()
{
}

QModelIndex
GrooveSongsModel::index (int row, int column, const QModelIndex &parent) const
{
  Q_UNUSED (parent);

  /* list size is 0 based */
  if (row < 0 || row >= m_songs.count () || column < 0 || column > m_visible.size () - 1)
    return QModelIndex ();

  return createIndex (row, column);
}

QModelIndex
GrooveSongsModel::parent (const QModelIndex &child) const
{
  Q_UNUSED (child);

  return QModelIndex ();
}

int
GrooveSongsModel::rowCount (const QModelIndex &parent) const
{
  Q_UNUSED (parent);

  return m_songs.count ();
}

int
GrooveSongsModel::columnCount (const QModelIndex &parent) const
{
  Q_UNUSED (parent);

  return m_visible.size ();
}

QVariant
GrooveSongsModel::data (const QModelIndex &index, int role) const
{
  if (GROOVE_VERIFY (index.row () >= 0, "row is negative"))
    return QVariant ();
  if (GROOVE_VERIFY (index.row () < m_songs.count (), "row is higher than the number of songs I have"))
    return QVariant ();
  if (GROOVE_VERIFY (index.column () >= 0, "column is negative"))
    return QVariant ();
  if (GROOVE_VERIFY (index.column () < m_visible.size (), "column is higher than m_visible.size ()"))
    return QVariant ();

  switch (role)
    {
    case Qt::DisplayRole:
      return m_songs[index.row ()]->property (m_visible[index.column ()].toUtf8 ());
    }

  return QVariant ();
}

QVariant
GrooveSongsModel::headerData (int section, Qt::Orientation orientation, int role) const
{
  if (orientation == Qt::Vertical)
    return QVariant ();

  if (GROOVE_VERIFY (section >= 0, "section is negative"))
    return QVariant ();
  if (GROOVE_VERIFY (section < m_visible.size (), "section is higher than m_visible.size ()"))
    return QVariant ();

  switch (role)
    {
    case Qt::DisplayRole:
      return tr (propNames[m_visible[section]]);
    }

  return QVariant ();
}

void
GrooveSongsModel::addVisible (QString const &item)
{
  m_visible.append (item);
}

void
GrooveSongsModel::beginChangeVisible ()
{
  emit beginResetModel ();

  m_visible.clear ();
}

void
GrooveSongsModel::endChangeVisible ()
{
  emit endResetModel ();
}

bool
GrooveSongsModel::isVisible (QString const &item)
{
  return m_visible.contains (item);
}

/*****/


int
GrooveSongsModel::count () const
{
  return rowCount (QModelIndex ());
}

void
GrooveSongsModel::clear ()
{
  emit beginResetModel ();

  /* Decrement reference count on all our songs (this will automatically delete ones with no references left) */
  foreach (GrooveSong *song, m_songs)
    song->deref ();

  m_songs.clear ();

  emit endResetModel ();
}
