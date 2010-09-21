/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#if HAVE_DEBUGLIB
#include "common/debug/backtrace.h"
#include "common/debug/trace.h"
#endif

#include <sys/resource.h>
#include <unistd.h>

static void
limit ()
{
  // 2048 MiB address space
  {
    struct rlimit const rlim = {
      2048u * 1024 * 1024,
      2048u * 1024 * 1024,
    };
    setrlimit (RLIMIT_AS, &rlim);
  }
  // 8 MiB stack
  {
    struct rlimit const rlim = {
      8 * 1024 * 1024,
      8 * 1024 * 1024,
    };
    setrlimit (RLIMIT_STACK, &rlim);
  }
}


void
init_debuglib ()
{
  limit ();
#if HAVE_DEBUGLIB
  init_debug ();
#endif
}

void
uninit_debuglib ()
{
}
