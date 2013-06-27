/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

#include "artistptr.h"

#include <QDate>
#include <QString>
#include <QVariantMap>
class QNetworkReply;

#include <memory>

class LIBGROOVESHARED_EXPORT GrooveArtist
  : public QObject
{
  Q_OBJECT

  friend void intrusive_ptr_add_ref (GrooveArtist *artist);
  friend void intrusive_ptr_release (GrooveArtist *artist);

  GrooveArtist (QVariantMap const &data);
  ~GrooveArtist ();

  void ref ();
  void deref ();

public:
  static GrooveArtistPointer make (QVariantMap const &data);

  Q_PROPERTY (int artistID READ artistID)                               int artistID () const;
  Q_PROPERTY (QString artistName READ artistName)                       QString artistName () const;

private:
  struct Data;
  std::auto_ptr<Data> d;
};
