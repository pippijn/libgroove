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
#include "groove/searchmodel.h"
#include "groove/settings.h"
#include "groove/data/song.h"

#include <QVariantMap>

GrooveSearchModel::GrooveSearchModel (std::shared_ptr<GrooveClient> client, std::shared_ptr<GrooveService> service, QObject *parent)
  : GrooveSongsModel (GrooveSettings::section::SEARCH, parent)
  , m_client (client)
  , m_service (service)
{
}

GrooveSearchModel::~GrooveSearchModel ()
{
  clear ();
}

void
GrooveSearchModel::searchByArtist (QString const &artist)
{
  searchByHelper ("Artists", artist);
}

void
GrooveSearchModel::searchBySong (QString const &song)
{
  searchByHelper ("Songs", song);
}

void
GrooveSearchModel::searchByAlbum (QString const &album)
{
  searchByHelper ("Albums", album);
}

/****/

void
GrooveSearchModel::searchByHelper (QString const &type, QString const &searchTerm)
{
  LDEBUG << "Searching by " << type << " for " << searchTerm;

  connect ( m_service.get ()
          , SIGNAL (getSearchResultsEx_success (QList<GrooveSongPointer> const &))
          , SLOT (processSearchCompleted (QList<GrooveSongPointer> const &))
          );
  QStringList types;
  types.append (type);
  m_service->getSearchResultsEx (searchTerm, types);
}

void
GrooveSearchModel::processSearchCompleted (QList<GrooveSongPointer> const &newSongList)
{
  disconnect (m_service.get (), SIGNAL (getSearchResultsEx_success (QList<GrooveSongPointer> const &)));

  if (!newSongList.count ())
    {
      LDEBUG << "Search found " << m_songs.count () << " songs";
      return;
    }

  beginInsertRows (QModelIndex (), 0, newSongList.count () - 1);
  clear ();
  m_songs = newSongList;
  endInsertRows ();

  emit searchCompleted (newSongList.size ());
}
