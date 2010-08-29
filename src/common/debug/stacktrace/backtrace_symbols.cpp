/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "common/debug/backtrace.h"
#include "common/util/xassert.h"

#include "stacktrace.h"

#include "frame.h"

backtrace_status_fn *backtrace_status;

std::vector<stacktrace::frame>
stacktrace::backtrace_symbols (void *const *buffer, size_t size)
{
  xassert (buffer);
  xassert (size > 0);

  size_t const skip = 0;
  size_t const ignore = 2;

  size_t stack_depth = size - skip - ignore;
  std::vector<frame> frames;

  if (!check_bfd ())
    {
      for (size_t x = skip; x < stack_depth; ++x)
        frames.emplace_back (frame { "func", "file", 0 });
      return frames;
    }

#if HAVE_BFD_H
  xassert (pthread_mutex_lock (&mtx) == 0);

  for (size_t x = skip; x < stack_depth; ++x)
    {
      if (backtrace_status)
        backtrace_status (x, stack_depth);
      frames.push_back (resolve_frame_internal (static_cast<char const *> (buffer[x])));
    }
  if (backtrace_status)
    backtrace_status (stack_depth, stack_depth);

  xassert (pthread_mutex_unlock (&mtx) == 0);

  return frames;
#endif
}
