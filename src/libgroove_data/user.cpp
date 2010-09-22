/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "groove/data/user.h"

struct GrooveUser::Data
{
  QVariantMap m_data;
  QAtomicInt m_refCount;

  Data (QVariantMap const &data)
    : m_data (data)
    , m_refCount (0)
  {
  }
};

inline GrooveUser::GrooveUser (QVariantMap const &data)
  : d (new Data (data))
{
}

GrooveUser::~GrooveUser ()
{
  printf ("bye %p\n", this);
}

inline void
GrooveUser::ref ()
{
  d->m_refCount.ref ();
}

inline void
GrooveUser::deref ()
{
  if (!d->m_refCount.deref ())
    deleteLater ();
}

GrooveUserPointer
GrooveUser::make (QVariantMap const &data)
{
  return new GrooveUser (data);
}

void
intrusive_ptr_add_ref (GrooveUser *user)
{
  user->ref ();
}

void
intrusive_ptr_release (GrooveUser *user)
{
  user->deref ();
}


int
GrooveUser::userID () const
{
  return d->m_data["userID"].toInt ();
}

QString
GrooveUser::username () const
{
  return d->m_data["username"].toString ();
}

bool
GrooveUser::isPremium () const
{
  return d->m_data["isPremium"].toBool ();
}

bool
GrooveUser::autoAutoplay () const
{
  return d->m_data["autoAutoplay"].toBool ();
}

int
GrooveUser::favoritesLimit () const
{
  return d->m_data["favoritesLimit"].toInt ();
}

int
GrooveUser::librarySizeLimit () const
{
  return d->m_data["librarySizeLimit"].toInt ();
}

bool
GrooveUser::uploadsEnabled () const
{
  return d->m_data["uploadsEnabled"].toBool ();
}

QString
GrooveUser::themeID () const
{
  return d->m_data["themeID"].toString ();
}

QString
GrooveUser::authToken () const
{
  return d->m_data["authToken"].toString ();
}

bool
GrooveUser::badAuthToken () const
{
  return d->m_data["badAuthToken"].toBool ();
}

uint
GrooveUser::privacy () const
{
  return d->m_data["privacy"].toUInt ();
}

uint
GrooveUser::flags () const
{
  return d->m_data["flags"].toUInt ();
}

QString
GrooveUser::sex () const
{
  return d->m_data["sex"].toString ();
}

QString
GrooveUser::email () const
{
  return d->m_data["email"].toString ();
}

QDate
GrooveUser::tsDOB () const
{
  return d->m_data["tsDOB"].toDate ();
}
