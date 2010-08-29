#pragma once

#include "common/util/common.h"

#include <csignal>

extern VISIBLE unsigned long stack_end;

VISIBLE bool fork_trace ();
VISIBLE void fork_abort (char const *msg);

#if __WORDSIZE == 64
# define init_debug()    \
   asm ("movq %%rbp, %0" : "=a" (stack_end));
#else
# define init_debug()    \
   asm ("movl %%ebp, %0" : "=a" (stack_end));
#endif
