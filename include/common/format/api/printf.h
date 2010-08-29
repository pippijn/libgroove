#include "common/format/Formatter.h"
#include "common/format/Interpreter.h"

struct StdoutPrinter
  : Interpreter<StdoutPrinter>
{
  template<typename ForwardIterator, typename... Args>
  void printf (ForwardIterator it, ForwardIterator et, Args const &...args)
  {
    length = 0;
    Interpreter<StdoutPrinter>::printf (it, et, args...);
  }

  void write (char const *data, size_t length)
  {
    this->length += fwrite (data, 1, length, stdout);
  }

  size_t length;
};

template<typename... Args>
int ts_printf (char const *fmt, Args const &...args)
{
  static StdoutPrinter out;
  static Formatter<StdoutPrinter> interp (out);
  interp.printf (fmt, args...);
  return out.length;
}
