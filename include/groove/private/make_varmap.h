/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

#include <QList>
#include <QVariant>
#include <QVarLengthArray>
#include <QVector>

#include <vector>
#include <utility>

struct QVariantOrMap
{
  typedef std::pair<char const *, QVariantOrMap> pair;
  typedef std::vector<pair>                      map;
  typedef QVarLengthArray<QVariant>              array;

  template<typename T>
  QVariantOrMap (QList<T> const &list)
    : scalar_value ()
    , map_value ()
    , array_value ()
  {
    foreach (T const &v, list)
      array_value.append (v);
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
    return !isScalar ()
        && !isMap ()
        && !isArray ()
         ;
  }

  bool isScalar () const { return scalar_value.isValid (); }
  bool isMap    () const { return !map_value.empty (); }
  bool isArray  () const { return !array_value.isEmpty (); }

  QVariant scalar_value;
  map map_value;
  array array_value;
};

static inline QVariantList
make_varlist (QVariantOrMap::array const &array_value)
{
  QVariantList list;
  qCopy (array_value.data (), array_value.data () + array_value.size (), std::back_inserter (list));
  return list;
}

static inline QVariantMap
make_varmap (QVariantOrMap::map const &map_value)
{
  QVariantMap map;

  foreach (QVariantOrMap::map::const_reference value, map_value)
    {
      if (value.second.isScalar ())
        map.insert (value.first, value.second.scalar_value);
      else if (value.second.isArray ())
        map.insert (value.first, make_varlist (value.second.array_value));
      else
        map.insertMulti (value.first, make_varmap (value.second.map_value));
    }
  return map;
}

static inline void
operator << (QVariantMap &request, QVariantOrMap::map const &map_value)
{
  request.unite (make_varmap (map_value));
}
