#include "common/format/FormatterBase.h"

#include "common/format/private/Parser.h"

FormatterBase::FormatterBase ()
  : parser (new Parser)
{
}

FormatterBase::~FormatterBase ()
{
  delete parser;
}

std::vector<Specification> const &
FormatterBase::analyse (char const *fmt, size_t expect)
{
  return parser->analyse (fmt, expect);
}
