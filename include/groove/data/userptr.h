/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

class GrooveUser;

#include <boost/intrusive_ptr.hpp>

typedef boost::intrusive_ptr<GrooveUser> GrooveUserPointer;

LIBGROOVESHARED_EXPORT void intrusive_ptr_add_ref (GrooveUser *user);
LIBGROOVESHARED_EXPORT void intrusive_ptr_release (GrooveUser *user);
