#include "common/format/Formatter.h"
#include "common/format/Interpreter.h"

#include "common/format/api/printf.h"
#include "common/format/api/snprintf.h"

#include <boost/format.hpp>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <tuple>

#include <sys/time.h>

static auto const OUTPUT              = 0;
static auto const ITERATIONS          = 100000u;
static auto const ROUNDS              = 10u;

static auto const TIME_FORMATTER        = 1;
static auto const TIME_SNPRINTF         = 1;
static auto const TIME_IOSTREAM         = 1;
static auto const TIME_BOOST_FORMAT     = 0;

struct Outputter
  : Interpreter<Outputter>
{
  template<typename ForwardIterator, typename... Args>
  void printf (ForwardIterator it, ForwardIterator et, Args ...args)
  {
    Interpreter<Outputter>::printf (it, et, args...);
  }

  void write (char const* data, size_t length)
  {
    if (OUTPUT)
      fwrite (data, 1, length, stdout);
  }
};

typedef uint64_t cycles_t;

static inline cycles_t
rdtsc ()
{
  uint32_t high;
  uint32_t low;
  asm volatile ("rdtsc" : "=d" (high), "=a" (low));
  return cycles_t (high) << 32
       | cycles_t (low)
       ;
}


#define TIME_START                                      \
  cycles_t time = std::numeric_limits<cycles_t>::max ();\
  for (size_t i = 0; i < max; i++)                      \
    {                                                   \
      cycles_t start = rdtsc ();

#define TIME_END                                        \
      cycles_t end = rdtsc ();                          \
      time = std::min (time, end - start);              \
    }                                                   \
  return time

template<size_t N>
static cycles_t do_format (size_t max);

template<>
cycles_t
do_format<0> (size_t max)
{
  TIME_START {
  } TIME_END;
}

template<>
cycles_t
do_format<1> (size_t max)
{
  Outputter writer;
  Formatter<Outputter> formatter (writer);
  TIME_START {
    //formatter.printf ("nothing: %% hex: 0x%x string: %s decimal: %d\n", 0x12345678, "hello", 1234);
    formatter.printf ("nothing: %% number: 0x%x string: %s float: %f\n", 0x12345678, "hello", 1234.3456789);
  } TIME_END;
}

template<>
cycles_t
do_format<2> (size_t max)
{
  char buf[1024];
  TIME_START {
    snprintf (buf, sizeof buf, "nothing: %% number: 0x%x string: %s float: %f\n", 0x12345678, "hello", 1234.3456789);
  } TIME_END;
}

template<>
cycles_t
do_format<3> (size_t max)
{
  std::stringstream ss;
  TIME_START {
    ss << "nothing: %% number: " << std::hex << 0x12345678 << " string: " << "hello" << " float: " << 1234.3456789 << "\n";
    ss.str ("");
  } TIME_END;
}

template<>
cycles_t
do_format<4> (size_t max)
{
  TIME_START {
    boost::format ("nothing: %% number: %x string: %s float: %f\n") % 0x12345678 % "hello" % 1234.56789;
  } TIME_END;
}

typedef std::pair<double, cycles_t> timing_t;

template<size_t N, size_t Max>
static void
do_timing (std::tuple<timing_t, timing_t, timing_t, timing_t, timing_t> &time, cycles_t delay)
{
  timeval start, end, diff;
  gettimeofday (&start, NULL);
  std::get<N> (time).second = std::min (do_format<N> (Max), std::get<N> (time).second) - delay;
  gettimeofday (&end, NULL);
  timersub (&end, &start, &diff);
  std::get<N> (time).first = std::min (double (diff.tv_sec) + double (diff.tv_usec) / 1000000, std::get<N> (time).first);
}

template<size_t Max>
static cycles_t
calibrate ()
{
  cycles_t delay = std::numeric_limits<cycles_t>::max ();
  printf ("calibrating delay loop: ");
  fflush (stdout);
  delay = std::min (do_format<0> (Max), delay);
  printf ("%llu\n", delay);

  return delay;
}

namespace std
{
  template<>
  struct numeric_limits<timing_t>
  {
    static timing_t max ()
    {
      return {
        numeric_limits<double>::max (),
        numeric_limits<cycles_t>::max (),
      };
    }
  };
}

#include <sched.h>

static void
init_rt ()
{
  sched_param param;
  param.sched_priority = sched_get_priority_max (SCHED_FIFO);
  if (sched_setscheduler (0, SCHED_FIFO, &param) != 0)
    perror ("cannot set real-time priority");
}

static void
test_printf ()
{
  ts_printf ("%% hello %s, say %d %s\n", "world", 123, "test");

  char buf[] = "aaaaaaa";
  ts_snprintf (buf, sizeof buf, "%s%s%s%s%s%s%s", "a", "a", "a", "a", "a", "a", "b");
  puts (buf);
}

int
main ()
{
  init_rt ();

  if (OUTPUT)
    {
      do_format<1> (1);
    }
  else
    {
      std::tuple<timing_t, timing_t, timing_t, timing_t, timing_t> time {
        std::numeric_limits<timing_t>::max (),
        std::numeric_limits<timing_t>::max (),
        std::numeric_limits<timing_t>::max (),
        std::numeric_limits<timing_t>::max (),
        std::numeric_limits<timing_t>::max (),
      };
      cycles_t delay = calibrate<ITERATIONS> ();
      for (size_t m = 0; m < ROUNDS; m++)
        {
          printf ("timing round %d", m + 1);
          fflush (stdout);

          if (TIME_FORMATTER)           do_timing<1, ITERATIONS> (time, delay);
          if (TIME_SNPRINTF)            do_timing<2, ITERATIONS> (time, delay);
          if (TIME_IOSTREAM)            do_timing<3, ITERATIONS> (time, delay);
          if (TIME_BOOST_FORMAT)        do_timing<4, ITERATIONS> (time, delay);
          fputc ('\r', stdout);
        }

      printf ("\nminimum time over %d rounds, formatting %d times\n", ROUNDS, ITERATIONS);
      if (TIME_FORMATTER)       printf ("formatter: %f sec\n", std::get<1> (time).first);
      if (TIME_SNPRINTF)        printf ("snprintf : %f sec\n", std::get<2> (time).first);
      if (TIME_IOSTREAM)        printf ("iostream : %f sec\n", std::get<3> (time).first);
      if (TIME_BOOST_FORMAT)    printf ("boost    : %f sec\n", std::get<4> (time).first);

      printf ("\nminimum number of cycles over %d rounds, formatting %d times\n", ROUNDS, ITERATIONS);
      if (TIME_FORMATTER)       printf ("formatter: %llu cycles\n", std::get<1> (time).second);
      if (TIME_SNPRINTF)        printf ("snprintf : %llu cycles\n", std::get<2> (time).second);
      if (TIME_IOSTREAM)        printf ("iostream : %llu cycles\n", std::get<3> (time).second);
      if (TIME_BOOST_FORMAT)    printf ("boost    : %llu cycles\n", std::get<4> (time).second);
    }
}
