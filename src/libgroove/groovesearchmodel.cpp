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
#include "groovesearchmodel.h"
#include "groove/settings.h"
#include "groove/song.h"

#include "groove/private/request.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QVariantMap>

#include <qjson/parser.h>

GrooveSearchModel::GrooveSearchModel (std::shared_ptr<GrooveClient> client, QObject *parent)
  : GrooveSongsModel (GrooveSettings::section::SEARCH, parent)
  , m_client (client)
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
  qDebug () << Q_FUNC_INFO << "Searching by " << type << " for " << searchTerm;

  GrooveRequest request (*m_client, GrooveRequest::more ("getSearchResults"));

  typedef QVariantOrMap::map map;
  request << map {
    { "method", "getSearchResults" },
    { "header", map {
        { "session", m_client->phpCookie ().toUtf8 () },
        { "token", m_client->grooveMessageToken ("getSearchResults") },
        { "client", "gslite" },
        { "clientRevision", GrooveRequest::REVISION },
      },
    },
    { "parameters", map {
        { "type", type },
        { "query", searchTerm },
      },
    },
  };

  request.post (this, SLOT (searchCompleted ()));
}

void
GrooveSearchModel::searchCompleted ()
{
  QNetworkReply *reply = qobject_cast<QNetworkReply *> (sender ());

  if (GROOVE_VERIFY (reply, "search returned without a QNetworkReply"))
    return;

  QByteArray response = reply->readAll ();
  QJson::Parser parser;
  bool ok;
  QVariantMap result = parser.parse (response, &ok).toMap ();
  if (GROOVE_VERIFY (ok, "error occurred whilst parsing search results"))
    return;

  QList<GrooveSongPointer > newSongList;
  foreach (QVariant const &song, result["result"].toList ())
    {
      QVariantMap songData = song.toMap ();

      newSongList.append (GrooveSong::make (m_client, songData));
    }

  if (!newSongList.count ())
    return;

  beginInsertRows (QModelIndex (), 0, newSongList.count () - 1);
  clear ();
  m_songs = newSongList;
  endInsertRows ();

  qDebug () << Q_FUNC_INFO << "Search found " << m_songs.count () << " songs";
}

GrooveSongPointer
GrooveSearchModel::songByIndex (QModelIndex const &index) const
{
  if (GROOVE_VERIFY (index.row () >= 0, "row is negative"))
    return 0;
  if (GROOVE_VERIFY (index.row () < m_songs.count (), "row is higher than the number of songs model contains"))
    return 0;

  return m_songs[index.row ()];
}
