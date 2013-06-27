/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

#include "albumptr.h"

#include <QDate>
#include <QString>
#include <QVariantMap>
class QNetworkReply;

#include <memory>

class LIBGROOVESHARED_EXPORT GrooveAlbum
  : public QObject
{
  Q_OBJECT

  friend void intrusive_ptr_add_ref (GrooveAlbum *album);
  friend void intrusive_ptr_release (GrooveAlbum *album);

  GrooveAlbum (QVariantMap const &data);
  ~GrooveAlbum ();

  void ref ();
  void deref ();

public:
  static GrooveAlbumPointer make (QVariantMap const &data);

  Q_PROPERTY (int albumID READ albumID)                                 int albumID () const;
  Q_PROPERTY (QString albumName READ albumName)                         QString albumName () const;
  Q_PROPERTY (int artistID READ artistID)                               int artistID () const;
  Q_PROPERTY (QString artistName READ artistName)                       QString artistName () const;
  Q_PROPERTY (QString artFilename READ artFilename)                     QString artFilename () const;

private:
  struct Data;
  std::auto_ptr<Data> d;
};
