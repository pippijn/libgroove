/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

class GrooveAlbum;

#include <boost/intrusive_ptr.hpp>

typedef boost::intrusive_ptr<GrooveAlbum> GrooveAlbumPointer;

LIBGROOVESHARED_EXPORT void intrusive_ptr_add_ref (GrooveAlbum *album);
LIBGROOVESHARED_EXPORT void intrusive_ptr_release (GrooveAlbum *album);
