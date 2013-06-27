/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

#include "userptr.h"

#include <QDate>
#include <QString>
#include <QVariantMap>
class QNetworkReply;

#include <memory>

class LIBGROOVESHARED_EXPORT GrooveUser
  : public QObject
{
  Q_OBJECT

  friend void intrusive_ptr_add_ref (GrooveUser *user);
  friend void intrusive_ptr_release (GrooveUser *user);

  GrooveUser (QVariantMap const &data);
  ~GrooveUser ();

  void ref ();
  void deref ();

public:
  static GrooveUserPointer make (QVariantMap const &data);

  Q_PROPERTY (int userID READ userID)                                   int userID () const;
  Q_PROPERTY (QString username READ username)                           QString username () const;
  Q_PROPERTY (bool isPremium READ isPremium)                            bool isPremium () const;
  Q_PROPERTY (bool autoAutoplay READ autoAutoplay)                      bool autoAutoplay () const;
  Q_PROPERTY (int favoritesLimit READ favoritesLimit)                   int favoritesLimit () const;
  Q_PROPERTY (int librarySizeLimit READ librarySizeLimit)               int librarySizeLimit () const;
  Q_PROPERTY (bool uploadsEnabled READ uploadsEnabled)                  bool uploadsEnabled () const;
  Q_PROPERTY (QString themeID READ themeID)                             QString themeID () const;
  Q_PROPERTY (QString authToken READ authToken)                         QString authToken () const;
  Q_PROPERTY (bool badAuthToken READ badAuthToken)                      bool badAuthToken () const;
  Q_PROPERTY (uint privacy READ privacy)                                uint privacy () const;
  Q_PROPERTY (uint flags READ flags)                                    uint flags () const;
  Q_PROPERTY (QString sex READ sex)                                     QString sex () const;
  Q_PROPERTY (QString email READ email)                                 QString email () const;
  Q_PROPERTY (QDate tsDOB READ tsDOB)                                   QDate tsDOB () const;

private:
  struct Data;
  std::auto_ptr<Data> d;
};
