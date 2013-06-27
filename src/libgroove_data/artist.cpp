/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "groove/data/artist.h"

struct GrooveArtist::Data
{
  QVariantMap m_data;
  QAtomicInt m_refCount;

  Data (QVariantMap const &data)
    : m_data (data)
    , m_refCount (0)
  {
  }
};

inline GrooveArtist::GrooveArtist (QVariantMap const &data)
  : d (new Data (data))
{
}

GrooveArtist::~GrooveArtist ()
{
  printf ("bye %p\n", implicit_cast<void *> (this));
}

inline void
GrooveArtist::ref ()
{
  d->m_refCount.ref ();
}

inline void
GrooveArtist::deref ()
{
  if (!d->m_refCount.deref ())
    deleteLater ();
}

GrooveArtistPointer
GrooveArtist::make (QVariantMap const &data)
{
  return new GrooveArtist (data);
}

void
intrusive_ptr_add_ref (GrooveArtist *artist)
{
  artist->ref ();
}

void
intrusive_ptr_release (GrooveArtist *artist)
{
  artist->deref ();
}


int
GrooveArtist::artistID () const
{
  return d->m_data["ArtistID"].toInt ();
}

QString
GrooveArtist::artistName () const
{
  return d->m_data["Name"].toString ();
}
