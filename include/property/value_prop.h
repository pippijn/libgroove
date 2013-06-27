template
< typename Class
, typename T
, T const &get (Class const &, T const &)
, void set (Class &, T &, T const &)
, size_t offset ()
>
struct value_prop
{
  T value;

  Class &self ()
  {
    return *reinterpret_cast<Class *> (reinterpret_cast<char *> (this) - offset ());
  }

  Class const &self () const
  {
    return *reinterpret_cast<Class const *> (reinterpret_cast<char const *> (this) - offset ());
  }

  value_prop &operator   = (T const &rhs) { set (self (), value, rhs); return *this; }
  value_prop &operator  += (T const &rhs) { set (self (), value, get (self (), value)  + rhs); return *this; }
  value_prop &operator  -= (T const &rhs) { set (self (), value, get (self (), value)  - rhs); return *this; }
  value_prop &operator  *= (T const &rhs) { set (self (), value, get (self (), value)  * rhs); return *this; }
  value_prop &operator  /= (T const &rhs) { set (self (), value, get (self (), value)  / rhs); return *this; }
  value_prop &operator  %= (T const &rhs) { set (self (), value, get (self (), value)  % rhs); return *this; }
  value_prop &operator  |= (T const &rhs) { set (self (), value, get (self (), value)  | rhs); return *this; }
  value_prop &operator  &= (T const &rhs) { set (self (), value, get (self (), value)  & rhs); return *this; }
  value_prop &operator  ^= (T const &rhs) { set (self (), value, get (self (), value)  ^ rhs); return *this; }
  value_prop &operator <<= (T const &rhs) { set (self (), value, get (self (), value) << rhs); return *this; }
  value_prop &operator >>= (T const &rhs) { set (self (), value, get (self (), value) >> rhs); return *this; }

  operator T const & () const { return get (self (), value); }

  T       *operator -> ()       { return &const_cast<T &> (get (self (), value)); }
  T const *operator -> () const { return &                 get (self (), value) ; }
};

#define def_value_prop(T, Class, name, get, set)                        \
  static size_t offset_##name () { return offsetof (Class, name); }     \
  static T const &get_##name (Class const &self, T const &property) get \
  static void set_##name (Class &self, T &property, T const &value) set \
  ::value_prop<Class, T, get_##name, set_##name, offset_##name> name
