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

#include "groove/settings.h"
#include "groove/song.h"
#include "groove/songsmodel.h"

#include <QSettings>
#include <QTime>

#include <map>

static std::map<QString, char const *> const propNames = {
  { "songID",                   "Song ID"                       },
  { "albumID",                  "Album ID"                      },
  { "artistID",                 "Artist ID"                     },
  { "genreID",                  "Genre ID"                      },
  { "name",                     "Name"                          },
  { "songName",                 "Title"                         },
  { "albumName",                "Album"                         },
  { "artistName",               "Artist"                        },
  { "year",                     "Year"                          },
  { "trackNum",                 "Track"                         },
  { "coverArtFilename",         "Cover-art filename"            },
  { "TSAdded",                  "Time added"                    },
  { "avgRating",                "Average rating"                },
  { "avgDuration",              "Average duration (s)"          },
  { "estimateDuration",         "Duration (s)"                  },
  { "avgDurationMins",          "Average duration"              },
  { "estimateDurationMins",     "Duration"                      },
  { "flags",                    "Flags"                         },
  { "isLowBitrateAvailable",    "Is low bitrate available"      },
  { "songVerified",             "Song verified"                 },
  { "albumVerified",            "Album verified"                },
  { "artistVerified",           "Artist verified"               },
  { "popularity",               "Popularity"                    },
  { "albumPopularity",          "Album popularity"              },
  { "artistPopularity",         "Artist popularity"             },
  { "songPlays",                "Plays"                         },
  { "artistPlays",              "Artist plays"                  },
  { "songClicks",               "Clicks"                        },
  { "albumClicks",              "Album clicks"                  },
  { "artistClicks",             "Artist clicks"                 },
  { "querySongClicks",          "querySongClicks"               },
  { "queryAlbumClicks",         "queryAlbumClicks"              },
  { "queryArtistClicks",        "queryArtistClicks"             },
  { "sphinxWeight",             "Sphinx weight"                 },
  { "score",                    "Score"                         },
  { "DSName",                   "DSName"                        },
  { "DALName",                  "DALName"                       },
  { "DAName",                   "DAName"                        },
  { "TSAddedInt",               "TSAddedInt"                    },
  { "rank",                     "Rank"                          },
};

GrooveSongsModel::GrooveSongsModel (QString const &modelName, QObject *parent)
  : QAbstractItemModel (parent)
  , m_modelName (modelName)
{
  QSettings settings;
  settings.beginGroup (m_modelName);
  if (!settings.contains (GrooveSettings::COLUMNS))
    {
      m_visible.append ("songName");
      m_visible.append ("albumName");
      m_visible.append ("artistName");
      m_visible.append ("estimateDuration");
    }
  else
    {
      GROOVE_VERIFY_OR_DIE (settings.value (GrooveSettings::COLUMNS).canConvert<QStringList> (),
                            "invalid configuration data for `columns' key");

      m_visible = settings.value (GrooveSettings::COLUMNS).toStringList ();
    }

  settings.endGroup ();
}

GrooveSongsModel::~GrooveSongsModel ()
{
  QSettings settings;
  settings.beginGroup (m_modelName);

  settings.setValue (GrooveSettings::COLUMNS, m_visible);

  settings.endGroup ();
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

  GrooveSong *song = m_songs[index.row ()];

  switch (role)
    {
    case Qt::DisplayRole:
      return song->property (m_visible[index.column ()].toUtf8 ());
    case Qt::ToolTipRole:
      return QString ("%1 %2 - %3 (%4) (%5)")
             .arg (song->trackNum ())
             .arg (song->artistName ())
             .arg (song->songName ())
             .arg (song->albumName ())
             .arg (song->estimateDurationMins ())
             ;
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
      GROOVE_VERIFY_OR_DIE (propNames.find (m_visible[section]) != propNames.end (), "invalid section");
      return tr (propNames.find (m_visible[section])->second);
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
