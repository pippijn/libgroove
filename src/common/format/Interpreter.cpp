#include "common/format/Interpreter.h"

#include "Interpreter/append_number.h"

#include <cassert>
#include <cstring>

void
InterpreterBase::format (Specification const &spec)
{
  if (spec.begin[0] == '%')
    write (spec.begin, 1);
  else
    write (spec.begin, spec.end - spec.begin);
}

static int
base (Conversion conversion)
{
  switch (conversion)
    {
    case Conversion::x:
    case Conversion::X:
      return 16;
    case Conversion::o:
      return 8;
    }
  return 10;
}

template<>
void
InterpreterBase::format (Specification const &spec, int value, int width, int precision)
{
  char buf[1000];
  char *ptr = buf;

  append_number ( ptr
                , buf + sizeof buf
                , value
                , base (spec.conversion)
                , width
                , precision
                , spec.conversion
                , spec.flags
                );
  write (buf, ptr - buf);
}

template<>
void
InterpreterBase::format (Specification const &spec, double value, int width, int precision)
{
  char buf[1000];
  if (spec.normal () && width == 0 && precision == 0)
    write (buf, snprintf (buf, sizeof buf, "%f", value));
  else
    assert (!"double formatting is not supported, yet");
}

template<>
void
InterpreterBase::format (Specification const &spec, char const *value, int width, int precision)
{
  char buf[1000];
  if (spec.normal () && width == 0 && precision == 0)
    write (value, strlen (value));
  else
    assert (!"string formatting is not supported, yet");
}
