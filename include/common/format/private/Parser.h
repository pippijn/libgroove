#pragma once

#include "common/format/FormatterBase.h"

#include <string>
#include <unordered_map>

#include <cstring>

char const *enum_name (Flag flag);
char const *enum_name (Length length);
char const *enum_name (Conversion conversion);
std::string operand_name (int masked);

struct string_hash
{
  /*
   * This is the "One-at-a-Time" algorithm by Bob Jenkins, also used by Perl's
   * hashes. (http://burtleburtle.net/bob/hash/doobs.html).
   * If you have the perl sources, look at hv.h, the definition for the
   * PERL_HASH macro.
   */
  size_t operator () (char const *k) const
  {
    unsigned long hash = 0;

    while (*k)
      {
        hash += *k++;
        hash += hash << 10;
        hash ^= hash >> 6;
      }
    hash += hash << 3;
    hash ^= hash >> 11;

    return hash + (hash << 15);
  }
};

struct string_equals
{
  size_t operator () (char const *s1, char const *s2) const
  {
    return strcmp (s1, s2) == 0;
  }
};

struct FormatterBase::Parser
{
  std::unordered_map<char const *, std::vector<Specification>, string_hash, string_equals> specs_map;
  std::vector<Specification> *specs;

  char const *begin;
  char const *current;
  char const *end;

  enum LexState
  {
    STRING,
    FORMAT,
  } state;

  std::vector<Specification> const &analyse (char const *fmt, size_t expect);
};
