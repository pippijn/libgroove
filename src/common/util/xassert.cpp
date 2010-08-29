/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include <sstream>

#include "common/util/xassert.h"

#include "common/util/array_size.h"
#include "common/util/auto_free.h"
#include "common/util/closure.h"
#include "common/util/common.h"
#include "common/util/force_assign.h"
#include "common/util/init_error.h"
#include "common/util/invoke_closure.h"
#include "common/util/make_closure.h"
#include "common/util/make_closure_each.h"
#include "common/util/output.h"
#include "common/util/phoenix.h"
#include "common/util/placeholder.h"
#include "common/util/preprocessor.h"
#include "common/util/string.h"
#include "common/util/type_traits/decay_array.h"
#include "common/util/type_traits/identity.h"
#include "common/util/type_traits/int_pack.h"
#include "common/util/type_traits/nth_type.h"
#include "common/util/type_traits/return_type.h"
#include "common/util/unimplemented.h"
#include "common/util/va_list.h"
#include "common/util/va_list_unpack.h"
#include "common/util/va_list_unpack0.h"
#include "common/util/va_list_unpackN.h"
#include "common/util/wrapper.h"
#include "common/util/xassert.h"

std::string
assertion_failure::construct (char const* msg, char const* file, int line, char const* func)
{
  std::ostringstream s;

  s << "Assertion `" << msg
    << "' failed at " << file << ':' << line
    << " in " << func;

  return s.str ();
}
