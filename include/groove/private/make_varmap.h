/*
 * Copyright © 2010 Pippijn van Steenhoven <pippijn@xinutec.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include "libgroove_global.h"

#include <QVariant>

#include <vector>
#include <utility>

struct QVariantOrMap
{
  typedef std::vector<std::pair<QString, QVariantOrMap>> map;

  QVariantOrMap (QVariant const &scalar_value)
    : scalar_value (scalar_value)
  {
  }

  QVariantOrMap (map const &map_value)
    : map_value (map_value)
  {
  }

  QVariant scalar_value;
  map map_value;
};

static inline QVariantMap
make_varmap (QVariantOrMap::map const &map_value)
{
  QVariantMap map;

  auto it = map_value.begin ();
  auto et = map_value.end ();
  
  while (it != et)
    {
      if (it->second.scalar_value.isValid ())
        {
          GROOVE_VERIFY_OR_DIE (it->second.map_value.empty (), "both map and scalar are set");
          map.insert (it->first, it->second.scalar_value);
        }
      else
        {
          GROOVE_VERIFY_OR_DIE (!it->second.map_value.empty (), "neither map nor scalar are set");
          map.insertMulti (it->first, make_varmap (it->second.map_value));
        }
      ++it;
    }
  return map;
}

static inline void
operator << (QVariantMap &request, QVariantOrMap::map const &map_value)
{
  request = make_varmap (map_value);
}
