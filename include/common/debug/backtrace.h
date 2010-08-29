/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include <stdio.h>

#include "common/util/common.h"

BEGIN_DECLS

/*
 * XXX: Lift arbitrary limits by allocating enough memory for all files,
 * functions and frame objects in one piece. This would save memory, too.
 * See backtrace_symbols.
 */
enum
{
  MAX_FILE = 64,
  MAX_FUNC = 512,
};

struct frame
{
  char file[MAX_FILE];
  char func[MAX_FUNC];
  long line;
};

typedef void print_fn (char const* fmt);
typedef void backtrace_status_fn (size_t cur, size_t max);

extern VISIBLE print_fn std_print;
extern VISIBLE backtrace_status_fn *backtrace_status;

VISIBLE char** backtrace_symbols (void* const* buffer, int size) NOTHROW;
VISIBLE char* resolve_symbol (void const* sym) NOTHROW;
VISIBLE struct frame* backtrace_frames_current (int skip DEFAULT_ARG (0)) NOTHROW;
VISIBLE struct frame* backtrace_frames (void* const* buffer, int size) NOTHROW;
VISIBLE void print_backtrace (print_fn print DEFAULT_ARG (std_print)) NOTHROW;
VISIBLE void print_frames (struct frame const* frames, print_fn print DEFAULT_ARG (std_print)) NOTHROW;

END_DECLS

#ifdef __cplusplus

// Small helper template that relieves client code from the need to cast.
template<typename R, typename... Args>
char* resolve_symbol (R sym (Args...))
{
  return resolve_symbol (reinterpret_cast<void const*> (sym));
}

#endif
