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

#pragma once

#include "libgroove_global.h"

#include "groove/data/songptr.h"

#include <QAbstractItemModel>
#include <QStringList>

class LIBGROOVESHARED_EXPORT GrooveSongsModel
  : public QAbstractItemModel
{
  Q_OBJECT

protected:
  GrooveSongsModel (QString const &modelName, QObject *parent);
  ~GrooveSongsModel ();

public:
  /*!
   *  Retrieve a song for a given \a index.
   *
   *  Returns a pointer to the song or 0 if there is an error.
   */
  GrooveSongPointer songByIndex (QModelIndex const &index) const;
  GrooveSongPointer songByIndex (int index) const;

private:
  bool validateIndex (QModelIndex const &index) const;

public:
  virtual QModelIndex index (int row, int column, QModelIndex const &parent = QModelIndex ()) const;
  virtual QModelIndex parent (QModelIndex const &child) const;
  virtual int rowCount (QModelIndex const &parent = QModelIndex ()) const;
  virtual int columnCount (QModelIndex const &parent = QModelIndex ()) const;
  virtual QVariant data (QModelIndex const &index, int role = Qt::DisplayRole) const;
  virtual QVariant headerData (int section, Qt::Orientation orientation, int role) const;
  virtual bool setData (QModelIndex const &index, QVariant const &value, int role = Qt::EditRole);

public:
  void addVisible (QString const &item);
  void beginChangeVisible ();
  void endChangeVisible ();
  bool isVisible (QString const &item);

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
  QString m_modelName;
  QList<GrooveSongPointer> m_songs;
  QStringList m_visible;
  QList<QVariantList> m_data;
};
