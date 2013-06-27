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

#include <map>

#include <QTime>
#include <QUrl>

#include "groove/settings.h"
#include "groove/data/song.h"
#include "groove/songsmodel.h"

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
  { "querySongClicks",          "Query song clicks"             },
  { "queryAlbumClicks",         "Query album clicks"            },
  { "queryArtistClicks",        "Query artist clicks"           },
  { "sphinxWeight",             "Sphinx weight"                 },
  { "score",                    "Score"                         },
  { "DSName",                   "DSName"                        },
  { "DALName",                  "DALName"                       },
  { "DAName",                   "DAName"                        },
  { "TSAddedInt",               "TSAddedInt"                    },
  { "rank",                     "Rank"                          },
};

static inline std::ostream &
operator << (std::ostream &cs, QModelIndex const &idx)
{
  return cs << "[" << idx.row () << "," << idx.column () << "]";
}

GrooveSongsModel::GrooveSongsModel (QString const &modelName, QObject *parent)
  : QAbstractItemModel (parent)
  , m_modelName (modelName)
  , m_songs ()
  , m_visible ()
  , m_data ()
{
  m_visible.append ("songName");
  m_visible.append ("albumName");
  m_visible.append ("artistName");
  m_visible.append ("coverArtFilename");
  m_visible.append ("estimateDuration");

  // for QML
  QHash<int, QByteArray> roles;

  for (int i = 0; i < columnCount (); i++)
    roles[Qt::UserRole + i] = m_visible[i].toUtf8 ();

  setRoleNames (roles);
}

GrooveSongsModel::~GrooveSongsModel ()
{
}


GrooveSongPointer
GrooveSongsModel::songByIndex (QModelIndex const &index) const
{
  return songByIndex (index.row ());
}

GrooveSongPointer
GrooveSongsModel::songByIndex (int index) const
{
  if (GROOVE_VERIFY (index >= 0, "row is negative"))
    return 0;
  if (GROOVE_VERIFY (index < rowCount (), "row is higher than the number of songs I have"))
    return 0;

  return m_songs[index];
}


bool
GrooveSongsModel::validateIndex (QModelIndex const &index) const
{
  if (GROOVE_VERIFY (index.row () >= 0, "row is negative"))
    return false;
  if (GROOVE_VERIFY (index.row () < rowCount (), "row is higher than the number of songs I have"))
    return false;
  if (GROOVE_VERIFY (index.column () >= 0, "column is negative"))
    return false;
  if (GROOVE_VERIFY (index.column () < columnCount (), "column is higher than columnCount ()"))
    return false;
  return true;
}


QModelIndex
GrooveSongsModel::index (int row, int column, QModelIndex const &parent) const
{
  Q_UNUSED (parent);

  /* list size is 0 based */
  if (row < 0 || row >= rowCount () || column < 0 || column > columnCount () - 1)
    return QModelIndex ();

  return createIndex (row, column);
}

QModelIndex
GrooveSongsModel::parent (QModelIndex const &child) const
{
  Q_UNUSED (child);

  return QModelIndex ();
}

int
GrooveSongsModel::rowCount (QModelIndex const &parent) const
{
  Q_UNUSED (parent);

  return m_songs.count ();
}

int
GrooveSongsModel::columnCount (QModelIndex const &parent) const
{
  Q_UNUSED (parent);

  return m_visible.size ();
}

QVariant
GrooveSongsModel::data (QModelIndex const &index, int role) const
{
  if (!validateIndex (index))
    return QVariant ();

  GrooveSongPointer song = songByIndex (index);

  int wantedData = index.column ();

  if (role >= Qt::UserRole)
    {
      // we do this to (mostly transparently) map QML roles to columns
      wantedData = role - Qt::UserRole;
      role = Qt::DisplayRole;
    }

  switch (role)
    {
    case Qt::DisplayRole:
      {
        QString const prop = m_visible[wantedData];
        QVariant const data = song->property (m_visible[wantedData].toUtf8 ());
        if (prop == "coverArtFilename")
          {
            QByteArray rawdata = data.toByteArray ();
            if (!rawdata.length ())
              return QUrl ("http://static.a.gs-cdn.net/webincludes/images/default/album_100.png");

            return QUrl ("http://beta.grooveshark.com/static/amazonart/m" + rawdata);
          }
        return data;
      }
    case Qt::ToolTipRole:
      {
        return QString ("%1 %2 - %3 (%4) (%5)")
               .arg (song->trackNum ())
               .arg (song->artistName ())
               .arg (song->songName ())
               .arg (song->albumName ())
               .arg (song->estimateDurationMins ())
               ;
      }
    }

#if 0
  LDEBUG << "getting data at " << index << " for role " << role << " out of " << data.size ();
#endif
  if (index.row () < m_data.size ())
    {
      QVariantList const &data = m_data[index.row ()];
      if (0 <= role && role < data.size ())
        return data[role];
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
  if (GROOVE_VERIFY (section < columnCount (), "section is higher than columnCount ()"))
    return QVariant ();

  switch (role)
    {
    case Qt::DisplayRole:
      auto found = propNames.find (m_visible[section]);
      GROOVE_VERIFY_OR_DIE (found != propNames.end (), "invalid section");
      return tr (found->second);
    }

  return QVariant ();
}

bool
GrooveSongsModel::setData (QModelIndex const &index, QVariant const &value, int role)
{
  if (index.row () == -1)
    return false;
  if (!validateIndex (index))
    return false;

#if 1
  LDEBUG << "setting " << index << " to " << value << " for role " << role;
#endif

  while (index.row () >= m_data.size ())
    m_data.push_back ({ });
  QVariantList &data = m_data[index.row ()];
  while (role >= data.size ())
    data.push_back ({ });
  data[role] = value;

#if 0
  LDEBUG << "columnCount = " << columnCount ();
#endif
  emit dataChanged (this->index (index.row (), 0),
                    this->index (index.row (), columnCount () - 1));

  return true;
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

  m_songs.clear ();

  emit endResetModel ();
}
