/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

class GrooveArtist;

#include <boost/intrusive_ptr.hpp>

typedef boost::intrusive_ptr<GrooveArtist> GrooveArtistPointer;

LIBGROOVESHARED_EXPORT void intrusive_ptr_add_ref (GrooveArtist *artist);
LIBGROOVESHARED_EXPORT void intrusive_ptr_release (GrooveArtist *artist);
