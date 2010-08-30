#include "common/debug/backtrace.h"
#include "common/debug/signal.h"
#include "common/debug/trace.h"

#include <sys/resource.h>
#include <unistd.h>

static void
limit ()
{
  // 512MiB address space
  {
    struct rlimit const rlim = {
      512 * 1024 * 1024,
      512 * 1024 * 1024,
    };
    setrlimit (RLIMIT_AS, &rlim);
  }
  // 8MiB stack
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
  init_signals ();
  init_debug ();
  limit ();
}

void
uninit_debuglib ()
{
  uninit_signals ();
}
