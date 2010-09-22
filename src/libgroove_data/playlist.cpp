/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "groove/data/playlist.h"

struct GroovePlaylist::Data
{
  QVariantMap m_data;
  QAtomicInt m_refCount;

  Data (QVariantMap const &data)
    : m_data (data)
    , m_refCount (0)
  {
  }
};

inline GroovePlaylist::GroovePlaylist (QVariantMap const &data)
  : d (new Data (data))
{
}

GroovePlaylist::~GroovePlaylist ()
{
  printf ("bye %p\n", implicit_cast<void *> (this));
}

inline void
GroovePlaylist::ref ()
{
  d->m_refCount.ref ();
}

inline void
GroovePlaylist::deref ()
{
  if (!d->m_refCount.deref ())
    deleteLater ();
}

GroovePlaylistPointer
GroovePlaylist::make (QVariantMap const &data)
{
  return new GroovePlaylist (data);
}

void
intrusive_ptr_add_ref (GroovePlaylist *playlist)
{
  playlist->ref ();
}

void
intrusive_ptr_release (GroovePlaylist *playlist)
{
  playlist->deref ();
}


int
GroovePlaylist::playlistID () const
{
  return d->m_data["PlaylistID"].toInt ();
}

QString
GroovePlaylist::playlistName () const
{
  return d->m_data["Name"].toString ();
}

int
GroovePlaylist::userID () const
{
  return d->m_data["UserID"].toInt ();
}

QString
GroovePlaylist::username () const
{
  return d->m_data["Username"].toString ();
}

QString
GroovePlaylist::description () const
{
  return d->m_data["About"].toString ();
}

QString
GroovePlaylist::artFilename () const
{
  return d->m_data["Picture"].toString ();
}
