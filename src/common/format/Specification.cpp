#include "common/format/private/Parser.h"

#include <sstream>

char const *
enum_name (Flag flag)
{
  static std::vector<std::string> names;
  static std::string name;

  names.clear ();

  if (flag == Flag::NONE)
    names.push_back ("NONE");
  if (int (flag) & int (Flag::Alternate))
    names.push_back ("Alternate");
  if (int (flag) & int (Flag::ZeroPadded))
    names.push_back ("ZeroPadded");
  if (int (flag) & int (Flag::LeftAdjusted))
    names.push_back ("LeftAdjusted");
  if (int (flag) & int (Flag::Blank))
    names.push_back ("Blank");
  if (int (flag) & int (Flag::Signed))
    names.push_back ("Signed");
  if (int (flag) & int (Flag::Grouped))
    names.push_back ("Grouped");
  if (int (flag) & int (Flag::Localised))
    names.push_back ("Localised");

  name.clear ();
  std::vector<std::string>::const_iterator it = names.begin ();
  std::vector<std::string>::const_iterator et = names.end ();
  while (it != et)
    {
      name += *it;
      ++it;
      if (it != et)
        name += " | ";
    }

  return name.c_str ();
}

char const *
enum_name (Length length)
{
  switch (length)
    {
    case Length::NONE: return "NONE";
    case Length::hh: return "hh";
    case Length::h: return "h";
    case Length::l: return "l";
    case Length::ll: return "ll";
    case Length::L: return "L";
    case Length::j: return "j";
    case Length::z: return "z";
    case Length::t: return "t";
    }

  return "<unknown>";
}

char const *
enum_name (Conversion conversion)
{
  switch (conversion)
    {
    case Conversion::NONE: return "NONE";
    case Conversion::d: return "d"; 
    case Conversion::i: return "i"; 
    case Conversion::o: return "o"; 
    case Conversion::u: return "u"; 
    case Conversion::x: return "x"; 
    case Conversion::X: return "X"; 
    case Conversion::e: return "e"; 
    case Conversion::E: return "E"; 
    case Conversion::f: return "f"; 
    case Conversion::F: return "F"; 
    case Conversion::g: return "g"; 
    case Conversion::G: return "G"; 
    case Conversion::a: return "a"; 
    case Conversion::A: return "A"; 
    case Conversion::c: return "c"; 
    case Conversion::s: return "s"; 
    case Conversion::p: return "p"; 
    case Conversion::n: return "n"; 
    case Conversion::m: return "m"; 
    }
  return "<unknown>";
}

std::string
operand_name (int masked)
{
  std::ostringstream ss;

  ss << (masked & ~Specification::OP_MASK);
  if (masked & Specification::OP_MASK)
    ss << " | OP_MASK";

  return ss.str ();
}

void
Specification::print (FILE *fh) const
{
  auto flags = enum_name (this->flags);
  auto length = enum_name (this->length);
  auto conversion = enum_name (this->conversion);
  auto operand = operand_name (this->operand);
  auto width = operand_name (this->width);
  auto precision = operand_name (this->precision);
  std::string string (this->begin, this->end);
  for (size_t nl = string.find ('\n');
       nl != std::string::npos;
       nl = string.find ('\n'))
    string.replace (nl, nl + 1, "\\n");

  fprintf (fh,
           "Specification {\n"
           "  flags     : %s\n"
           "  length    : %s\n"
           "  conversion: %s\n"
           "  operand   : %s\n"
           "  width     : %s\n"
           "  precision : %s\n"
           "\n"
           "  string    : `%s'\n"
           "}\n"
           , flags
           , length
           , conversion
           , operand.c_str ()
           , width.c_str ()
           , precision.c_str ()
           , string.c_str ());
}

bool
Specification::normal () const
{
  return flags == Flag::NONE
      && length == Length::NONE
      && conversion != Conversion::NONE
      && operand == 0
      && width == 0
      && precision == 0
      ;
}
