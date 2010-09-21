/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

#include <QList>
#include <QVariant>
#include <QVector>

#include <vector>
#include <utility>

struct QVariantOrMap
{
  typedef std::pair<char const *, QVariantOrMap> pair;
  typedef std::vector<pair>                      map;
  typedef std::vector<QVariant>                  array;

  template<typename T>
  QVariantOrMap (QList<T> const &list_value)
    : scalar_value ()
    , map_value ()
    , array_value ()
  {
    QVariantList list;
    foreach (T const &v, list_value)
      list.push_back (v);
  }

  template<typename T>
  QVariantOrMap (T const &scalar_value)
    : scalar_value (scalar_value)
    , map_value ()
    , array_value ()
  {
  }

  QVariantOrMap (map const &map_value)
    : scalar_value ()
    , map_value (map_value)
    , array_value ()
  {
  }

  QVariantOrMap (array const &array_value)
    : scalar_value ()
    , map_value ()
    , array_value (array_value)
  {
  }

  QVariantOrMap ()
    : scalar_value ()
    , map_value ()
    , array_value ()
  {
  }

  bool empty () const
  {
    return !scalar_value.isValid ()
        && map_value.empty ()
        && array_value.empty ()
         ;
  }

  QVariant scalar_value;
  map map_value;
  array array_value;
};

static inline QVariantMap
make_varmap (QVariantOrMap::map const &map_value)
{
  QVariantMap map;

  foreach (QVariantOrMap::map::const_reference value, map_value)
    {
      if (value.second.scalar_value.isValid ())
        {
          map.insert (value.first, value.second.scalar_value);
        }
      else if (!value.second.array_value.empty ())
        {
          map.insert (value.first, QList<QVariant>::fromVector (QVector<QVariant>::fromStdVector (value.second.array_value)));
        }
      else
        {
          map.insertMulti (value.first, make_varmap (value.second.map_value));
        }
    }
  return map;
}

static inline void
operator << (QVariantMap &request, QVariantOrMap::map const &map_value)
{
  request.unite (make_varmap (map_value));
}
