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

#ifndef GROOVESONGSMODEL_H
#define GROOVESONGSMODEL_H

#include "libgroove_global.h"

#include <QAbstractItemModel>

class GrooveSong;

class LIBGROOVESHARED_EXPORT GrooveSongsModel
  : public QAbstractItemModel
{
  Q_OBJECT

public:
  explicit GrooveSongsModel (QObject *parent = 0);

  virtual QModelIndex index (int row, int column, const QModelIndex &parent) const;
  virtual QModelIndex parent (const QModelIndex &child) const;
  virtual int rowCount (const QModelIndex &parent) const;
  virtual int columnCount (const QModelIndex &parent) const;
  virtual QVariant data (const QModelIndex &index, int role) const;
  virtual QVariant headerData (int section, Qt::Orientation orientation, int role) const;

  /*!
   *  Returns the number of tracks in this playlist.
   */
  int count () const;

public slots:
  /*!
   *  Clears this model of all songs, deleting songs which are not referred to in any other models.
   */
  void clear ();

protected:
  QList<GrooveSong *> m_songs;
};

#endif /* GROOVESONGSMODEL_H */
