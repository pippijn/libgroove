/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

class GroovePlaylist;

#include <boost/intrusive_ptr.hpp>

typedef boost::intrusive_ptr<GroovePlaylist> GroovePlaylistPointer;

LIBGROOVESHARED_EXPORT void intrusive_ptr_add_ref (GroovePlaylist *playlist);
LIBGROOVESHARED_EXPORT void intrusive_ptr_release (GroovePlaylist *playlist);
