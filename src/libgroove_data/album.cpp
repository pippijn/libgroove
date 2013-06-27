/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "groove/data/album.h"

struct GrooveAlbum::Data
{
  QVariantMap m_data;
  QAtomicInt m_refCount;

  Data (QVariantMap const &data)
    : m_data (data)
    , m_refCount (0)
  {
  }
};

inline GrooveAlbum::GrooveAlbum (QVariantMap const &data)
  : d (new Data (data))
{
}

GrooveAlbum::~GrooveAlbum ()
{
  printf ("bye %p\n", implicit_cast<void *> (this));
}

inline void
GrooveAlbum::ref ()
{
  d->m_refCount.ref ();
}

inline void
GrooveAlbum::deref ()
{
  if (!d->m_refCount.deref ())
    deleteLater ();
}

GrooveAlbumPointer
GrooveAlbum::make (QVariantMap const &data)
{
  return new GrooveAlbum (data);
}

void
intrusive_ptr_add_ref (GrooveAlbum *album)
{
  album->ref ();
}

void
intrusive_ptr_release (GrooveAlbum *album)
{
  album->deref ();
}


int
GrooveAlbum::albumID () const
{
  return d->m_data["albumID"].toInt ();
}

QString
GrooveAlbum::albumName () const
{
  return d->m_data["albumName"].toString ();
}

int
GrooveAlbum::artistID () const
{
  return d->m_data["artistID"].toInt ();
}

QString
GrooveAlbum::artistName () const
{
  return d->m_data["artistName"].toString ();
}

QString
GrooveAlbum::artFilename () const
{
  return d->m_data["artFilename"].toString ();
}
