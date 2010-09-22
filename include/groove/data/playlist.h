/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

#include "playlistptr.h"

#include <QDate>
#include <QString>
#include <QVariantMap>
class QNetworkReply;

#include <memory>

class LIBGROOVESHARED_EXPORT GroovePlaylist
  : public QObject
{
  Q_OBJECT

  friend void intrusive_ptr_add_ref (GroovePlaylist *playlist);
  friend void intrusive_ptr_release (GroovePlaylist *playlist);

  GroovePlaylist (QVariantMap const &data);
  ~GroovePlaylist ();

  void ref ();
  void deref ();

public:
  static GroovePlaylistPointer make (QVariantMap const &data);

  Q_PROPERTY (int playlistID READ playlistID)                           int playlistID () const;
  Q_PROPERTY (QString playlistName READ playlistName)                   QString playlistName () const;
  Q_PROPERTY (int userID READ userID)                                   int userID () const;
  Q_PROPERTY (QString username READ username)                           QString username () const;
  Q_PROPERTY (QString description READ description)                     QString description () const;
  Q_PROPERTY (QString artFilename READ artFilename)                     QString artFilename () const;

private:
  struct Data;
  std::auto_ptr<Data> d;
};
