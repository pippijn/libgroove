#pragma once

#include "FormatterBase.h"

#include <cassert>
#include <vector>

template<typename WorkerT>
struct Formatter
  : FormatterBase
{
  WorkerT &worker;

  Formatter (WorkerT &worker)
    : worker (worker)
  {
  }

  template<typename... Args>
  void printf (char const *fmt, Args const &...args)
  {
    std::vector<Specification> const &specs = analyse (fmt, sizeof... args);
    worker.printf (specs.begin (), specs.end (), args...);
  }
};
