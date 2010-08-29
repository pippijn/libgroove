#pragma once

#include "common/util/common.h"

#include "Specification.h"

#include <vector>

struct VISIBLE FormatterBase
{
  void *operator new (size_t) = delete; // no heap allocation (due to non-virtual dtor)
  FormatterBase (FormatterBase const &) = delete; // no copying
  FormatterBase& operator = (FormatterBase const &) = delete; // no copy assignment

  struct Parser;

private:
  Parser *parser;

protected:
  FormatterBase ();
  ~FormatterBase ();

  std::vector<Specification> const &analyse (char const *fmt, size_t expect);
};
