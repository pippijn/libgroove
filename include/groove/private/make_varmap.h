/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

#include <QVariant>

#include <vector>
#include <utility>

struct QVariantOrMap
{
  typedef std::vector<std::pair<char const *, QVariantOrMap>> map;

  template<typename T>
  QVariantOrMap (T const &scalar_value)
    : scalar_value (scalar_value)
    , map_value ()
  {
  }

  QVariantOrMap (map const &map_value)
    : scalar_value ()
    , map_value (map_value)
  {
  }

  QVariant scalar_value;
  map map_value;
};

static inline QVariantMap
make_varmap (QVariantOrMap::map const &map_value)
{
  QVariantMap map;

  foreach (QVariantOrMap::map::const_reference value, map_value)
    {
      if (value.second.scalar_value.isValid ())
        {
          GROOVE_VERIFY_OR_DIE (value.second.map_value.empty (), "both map and scalar are set");
          map.insert (value.first, value.second.scalar_value);
        }
      else
        {
          GROOVE_VERIFY_OR_DIE (!value.second.map_value.empty (), "neither map nor scalar are set");
          map.insertMulti (value.first, make_varmap (value.second.map_value));
        }
    }
  return map;
}

static inline void
operator << (QVariantMap &request, QVariantOrMap::map const &map_value)
{
  request = make_varmap (map_value);
}
