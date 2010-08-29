#pragma once

#include <cstdio>

/*
 * %[flags][min field width][precision][length]conversion specifier
 *   -----  ---------------  ---------  ------ -------------------
 *    \             #,*        .#, .*     /             \
 *     \                                 /               \
 *    #,0,-,+, ,',I                 hh,h,l,ll,j,z,L    c,d,u,x,X,e,f,g,s,p,%
 *    -------------                 ---------------    -----------------------
 *    # | Alternate,                 hh | char,           c | unsigned char,
 *    0 | zero pad,                   h | short,          d | signed int,
 *    - | left align,                 l | long,           u | unsigned int,
 *    + | explicit + - sign,         ll | long long,      x | unsigned hex int,
 *      | space for + sign,           j | [u]intmax_t,    X | unsigned HEX int,
 *    ' | locale thousands grouping,  z | size_t,         e | [-]d.ddde±dd double,
 *    I | Use locale's alt digits     t | ptrdiff_t,      E | [-]d.dddE±dd double,
 *                                    L | long double,  ---------=====
 *    if no precision   => 6 decimal places            /  f | [-]d.ddd double,
 *    if precision = 0  => 0 decimal places      _____/   g | e|f as appropriate,
 *    if precision = #  => # decimal places               G | E|F as appropriate,
 *    if flag = #       => always show decimal point      s | string,
 *                                              ..............------
 *                                             /          p | pointer,
 *    if precision      => max field width    /           % | %
 */
enum class Flag
{
  NONE,
  Alternate     = 1 << 0,
  ZeroPadded    = 1 << 1,
  LeftAdjusted  = 1 << 2,
  Blank         = 1 << 3,
  Signed        = 1 << 4,
  Grouped       = 1 << 5,
  Localised     = 1 << 6,
};

static inline bool
operator & (Flag lhs, Flag rhs)
{
  return Flag (int (lhs) & int (rhs)) != Flag::NONE;
}

static inline Flag
operator + (Flag lhs, Flag rhs)
{
  return Flag (int (lhs) | int (rhs));
}

static inline Flag operator -= (Flag& lhs, Flag rhs) { return lhs = Flag (int (lhs) & ~int (rhs)); }
static inline Flag operator += (Flag& lhs, Flag rhs) { return lhs = Flag (int (lhs) |  int (rhs)); }

enum class Length
  : unsigned char
{
  NONE, hh, h, l, ll, L, j, z, t
};

enum class Conversion
  : unsigned char
{
  NONE, d, i, o, u, x, X, e, E, f, F, g, G, a, A, c, s, p, n, m
};

struct Specification
{
  static int const OP_MASK = 1 << 15;

  Flag flags;
  Length length;
  Conversion conversion;
  int operand;
  int width;
  int precision;

  char const *begin;
  char const *end;

  void print (FILE *fh = stdout) const;
  // Normal means it's a bare format specification
  bool normal () const;
};
