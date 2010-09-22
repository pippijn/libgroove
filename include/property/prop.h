template
< typename Class
, typename T
, T get (Class const &)
, void set (Class &, T const &)
, size_t offset ()
>
struct prop
{
  Class &self ()
  {
    return *reinterpret_cast<Class *> (reinterpret_cast<char *> (this) - offset ());
  }

  Class const &self () const
  {
    return *reinterpret_cast<Class const *> (reinterpret_cast<char const *> (this) - offset ());
  }

  prop &operator   = (T const &rhs) { set (self (), rhs); return *this; }
  prop &operator  += (T const &rhs) { set (self (), get (self ())  + rhs); return *this; }
  prop &operator  -= (T const &rhs) { set (self (), get (self ())  - rhs); return *this; }
  prop &operator  *= (T const &rhs) { set (self (), get (self ())  * rhs); return *this; }
  prop &operator  /= (T const &rhs) { set (self (), get (self ())  / rhs); return *this; }
  prop &operator  %= (T const &rhs) { set (self (), get (self ())  % rhs); return *this; }
  prop &operator  |= (T const &rhs) { set (self (), get (self ())  | rhs); return *this; }
  prop &operator  &= (T const &rhs) { set (self (), get (self ())  & rhs); return *this; }
  prop &operator  ^= (T const &rhs) { set (self (), get (self ())  ^ rhs); return *this; }
  prop &operator <<= (T const &rhs) { set (self (), get (self ()) << rhs); return *this; }
  prop &operator >>= (T const &rhs) { set (self (), get (self ()) >> rhs); return *this; }

  operator T () const { return get (self ()); }

  T       *operator -> ()       { return &const_cast<T &> (get (self ())); }
  T const *operator -> () const { return &                 get (self ()) ; }
};

#define def_prop(T, Class, name, get, set)                              \
  static size_t offset_##name () { return offsetof (Class, name); }     \
  static T get_##name (Class const &self) get                           \
  static void set_##name (Class &self, T const &value) set              \
  ::prop<Class, T, get_##name, set_##name, offset_##name> name
