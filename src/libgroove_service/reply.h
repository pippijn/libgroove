#pragma once

#include <QVariantList>
#include <QVariantMap>

struct GrooveReply
{
  GrooveReply ()
    : value ()
  {
  }

  GrooveReply (QVariant const &value)
    : value (value)
  {
  }

  // TODO: optimise? does this create a new map every time?
  GrooveReply operator [] (char const *key)
  {
    return value.toMap ()[key];
  }

  operator int () const
  {
    return value.toInt ();
  }

  operator QString () const
  {
    return value.toString ();
  }

  operator QVariantList () const
  {
    return value.toList ();
  }

  operator QVariantMap () const
  {
    return value.toMap ();
  }

  QVariant const value;
};
