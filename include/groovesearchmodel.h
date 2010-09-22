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

#ifndef GROOVESEARCHREQUEST_H
#define GROOVESEARCHREQUEST_H

#include "libgroove_global.h"

#include "groove/data/songptr.h"
#include "groove/songsmodel.h"
class GrooveClient;
class GrooveService;

#include <memory>

class LIBGROOVESHARED_EXPORT GrooveSearchModel
  : public GrooveSongsModel
{
  Q_OBJECT

public:
  GrooveSearchModel (std::shared_ptr<GrooveClient> client, std::shared_ptr<GrooveService> service, QObject *parent);
  ~GrooveSearchModel ();

  /*!
   *  Retrieve a song for a given \a index.
   *
   *  Returns a pointer to the song or 0 if there is an error.
   */
  GrooveSongPointer songByIndex (QModelIndex const &index) const;

public slots:
  void searchByArtist (QString const &artist);  /* XXX: should this really be here? causes problems due to different fields returned? */
  void searchBySong (QString const &song);
  void searchByAlbum (QString const &album);  /* XXX: should this really be here? causes problems due to different fields returned? */

private:
  /*!
   *  Performs a search of the given \a type for a \a searchTerm on this model instance.
   *  Note that searches are asynchronous.
   */
  void searchByHelper (QString const &type, QString const &searchTerm);

private slots:
  /*!
   *  Invoked when a currently running search completes.
   */
  void searchCompleted (QList<GrooveSongPointer> const &newSongList);

private:
  std::shared_ptr<GrooveClient> m_client;
  std::shared_ptr<GrooveService> m_service;
};

#endif /* GROOVESEARCHREQUEST_H */
