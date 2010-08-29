#include <boost/foreach.hpp>

#include <cassert>
#include <cstring>

static int
yylex (YYSTYPE *lvalp, YYLTYPE *llocp, FormatterBase::Parser &parser)
{
  int retval = EOF;

  llocp->first_column = parser.current - parser.begin;
  switch (parser.state)
    {
    case FormatterBase::Parser::STRING:
      if (*parser.current == '%')
        {
          ++parser.current;
          parser.state = FormatterBase::Parser::FORMAT;
          retval = '%';
          break;
        }
      while (parser.current != parser.end)
        {
          retval = TEXT;
          if (*parser.current == '%')
            {
              parser.state = FormatterBase::Parser::FORMAT;
              break;
            }
          ++parser.current;
        }
      break;
    case FormatterBase::Parser::FORMAT:
      retval = *parser.current++;
      break;
    }

  llocp->last_column = parser.current - parser.begin;
  //printf ("(%d,%d): %c\n", llocp->first_column, llocp->last_column, retval == TEXT ? 'T' : retval);

  return retval;
}

static void
yyerror (YYLTYPE *llocp, FormatterBase::Parser &parser, char const *msg)
{
  printf ("at column %d: %s\n", llocp->first_column, msg);
  exit (0);
}

static size_t
expected (std::vector<Specification> const &specs)
{
  size_t count = 0;
  BOOST_FOREACH (Specification const &spec, specs)
    {
      if (spec.conversion != Conversion::NONE)
        ++count;
      if (spec.width & Specification::OP_MASK)
        ++count;
      if (spec.precision & Specification::OP_MASK)
        ++count;
    }
  return count;
}

std::vector<Specification> const&
FormatterBase::Parser::analyse (char const *fmt, size_t expect)
{
  assert (fmt != NULL);

  auto it = specs_map.find (fmt);
  if (it != specs_map.end ())
    return it->second;

  specs = &specs_map[fmt];

  begin = fmt;
  current = fmt;
  end = fmt + strlen (fmt);

  yyparse (*this);

  BOOST_FOREACH (Specification const &spec, *specs)
    {
      assert (spec.begin != NULL);
      assert (spec.end != NULL);
      assert (spec.begin >= begin); assert (spec.begin < end);
      assert (spec.end > begin); assert (spec.end <= end);
    }

  specs = NULL;

  auto found = specs_map.find (fmt);
  assert (found != specs_map.end ());
  assert (expect == expected (found->second) && "Not enough (or too many) arguments for format string");

  return found->second;
}
