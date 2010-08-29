#include <limits>

static void
append (char *&buf, char const *end, char c)
{
  if (buf + 1 < end)
    *buf++ = c;
}

// XXX: this implementation is both incomplete and broken, but it's an example
// of how to implement a printf-style formatting function
template<typename T>
static void
append_number ( char *&str
              , char const *end
              , T num
              , int base
              , int size
              , int precision
              , Conversion conv
              , Flag type
              )
{
  char tmp[36];
  char const *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  if (conv == Conversion::x)
    digits = "0123456789abcdefghijklmnopqrstuvwxyz";
  if (type & Flag::LeftAdjusted)
    type -= Flag::ZeroPadded;
  if (base < 2 || base > 36)
    return;
  char c = (type & Flag::ZeroPadded) ? '0' : ' ';
  signed char sign;
  if (std::numeric_limits<T>::is_signed && num < 0)
    {
      sign = '-';
      num = -num;
    }
  else
    sign = (type & Flag::Signed) ? '+' : ((type & Flag::Blank) ? ' ' : 0);
  if (sign)
    size--;
  if (type & Flag::Alternate)
    {
      if (base == 16)
        size -= 2;
      else if (base == 8)
        size--;
    }
  int i = 0;
  if (num == 0)
    tmp[i++] = '0';
  else
    while (num != 0)
      {
        tmp[i++] = digits[num % base];
        num /= base;
      }
  if (i > precision)
    precision = i;
  size -= precision;
  if (!(type & (Flag::ZeroPadded + Flag::LeftAdjusted)))
    while (size-- > 0)
      append (str, end, ' ');
  if (sign)
    append (str, end, sign);
  if (type & Flag::Alternate)
    {
      if (base == 8)
        append (str, end, '0');
      else if (base == 16)
        {
          append (str, end, '0');
          append (str, end, digits[33]);
        }
    }
  if (!(type & Flag::LeftAdjusted))
    while (size-- > 0)
      append (str, end, c);
  while (i < precision--)
    append (str, end, '0');
  while (i-- > 0)
    append (str, end, tmp[i]);
  while (size-- > 0)
    append (str, end, ' ');
}
