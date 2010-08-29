#pragma once

#include "common/util/common.h"

#include "Specification.h"

struct VISIBLE InterpreterBase
{
  void *operator new (size_t) = delete; // no heap allocation (due to non-virtual dtor)

protected:
  virtual void write (char const *data, size_t length) = 0;

  // basic formatter for plain string parts
  void format (Specification const &spec);
  // formatters for actual arguments
  template<typename T>
  void format (Specification const &spec, T value, int width = 0, int precision = 0);
};

template<typename Derived>
class Interpreter
  : InterpreterBase
{
  using InterpreterBase::format;

  Derived *self ()
  {
    return static_cast<Derived *> (this);
  }

  // skip plain strings or '%%'
  template<typename ForwardIterator>
  ForwardIterator format (ForwardIterator it, ForwardIterator et)
  {
    while (it != et && it->conversion == Conversion::NONE)
      {
        self ()->format (*it);
        ++it;
      }
    return it;
  }

  // write final parts (can only be strings or '%%')
  template<typename ForwardIterator>
  void interpret (ForwardIterator it, ForwardIterator et)
  {
    it = self ()->format (it, et);
    assert (it == et);
  }
  
  // format a single argument
  template<typename ForwardIterator, typename T1>
  void interpret (ForwardIterator it, ForwardIterator et, T1 v1)
  {
    it = self ()->format (it, et);
    assert (it != et);

    self ()->format (*it, v1);
    interpret (it + 1, et);
  }

  // format with either width or precision (or none)
  template<typename ForwardIterator, typename T, typename... Args>
  void interpret (ForwardIterator it, ForwardIterator et, int maybe_width_or_precision, T value, Args const &...args)
  {
    it = self ()->format (it, et);
    assert (it != et);

    if (it->width & Specification::OP_MASK)
      {
        self ()->format (*it, value, maybe_width_or_precision, 0);
        interpret (it + 1, et, args...);
      }
    else if (it->precision & Specification::OP_MASK)
      {
        self ()->format (*it, value, 0, maybe_width_or_precision);
        interpret (it + 1, et, args...);
      }
    else
      {
        self ()->format (*it, maybe_width_or_precision);
        interpret (it + 1, et, value, args...);
      }
  }

  // format with both width and precision (or none)
  template<typename ForwardIterator, typename T, typename... Args>
  void interpret (ForwardIterator it, ForwardIterator et, int maybe_width, int maybe_precision, T value, Args const &...args)
  {
    it = self ()->format (it, et);
    assert (it != et);

    if ((it->width & Specification::OP_MASK) && (it->precision & Specification::OP_MASK))
      {
        self ()->format (*it, value, maybe_width, maybe_precision);
        interpret (it + 1, et, args...);
      }
    else
      {
        self ()->format (*it, maybe_width);
        interpret (it + 1, et, maybe_precision, value, args...);
      }
  }

  // format anything else
  template<typename ForwardIterator, typename T, typename... Args>
  void interpret (ForwardIterator it, ForwardIterator et, T value, Args const &...args)
  {
    it = self ()->format (it, et);
    assert (it != et);

    self ()->format (*it, value);
    interpret (it + 1, et, args...);
  }

public:
  template<typename ForwardIterator, typename... Args>
  void printf (ForwardIterator it, ForwardIterator et, Args const &...args)
  {
    interpret (it, et, args...);
  }
};
