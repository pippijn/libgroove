#pragma once

#include <QVariantList>
#include <QVariantMap>

struct GrooveReply
{
  GrooveReply ()
    : m_value ()
  {
  }

  GrooveReply (QVariant const &value)
    : m_value (value)
  {
  }

  // TODO: optimise? does this create a new map every time?
  GrooveReply operator [] (char const *key)
  {
    return m_value.toMap ()[key];
  }

  operator int () const
  {
    return m_value.toInt ();
  }

  operator QString () const
  {
    return m_value.toString ();
  }

  operator QVariantList () const
  {
    return m_value.toList ();
  }

  operator QVariantMap () const
  {
    return m_value.toMap ();
  }

private:
  QVariant m_value;
};
