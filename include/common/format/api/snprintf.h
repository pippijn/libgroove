#include "common/format/Formatter.h"
#include "common/format/Interpreter.h"

struct BufferPrinter
  : Interpreter<BufferPrinter>
{
  template<typename ForwardIterator, typename... Args>
  void printf (ForwardIterator it, ForwardIterator et, Args const &...args)
  {
    length = 0;
    Interpreter<BufferPrinter>::printf (it, et, args...);
  }

  void write (char const *data, size_t length)
  {
    size_t minlen = std::min (length, maxlen);
    std::copy (data, data + minlen, buffer);
    this->length += minlen;
    this->buffer += minlen;
    this->maxlen -= minlen;
  }

  size_t length;
  size_t maxlen;
  char *buffer;
};

template<typename... Args>
int ts_snprintf (char *buffer, size_t maxlen, char const *fmt, Args const &...args)
{
  static BufferPrinter out;
  static Formatter<BufferPrinter> interp (out);
  out.buffer = buffer;
  out.maxlen = maxlen - 1;
  interp.printf (fmt, args...);
  *out.buffer = '\0';
  return out.length;
}

template<size_t maxlen, typename... Args>
int ts_snprintf (char (&buffer)[maxlen], char const *fmt, Args const &...args)
{
  return ts_snprintf (buffer, maxlen, fmt, args...);
}
