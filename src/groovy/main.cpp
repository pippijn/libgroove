/*
 * Copyright © 2010 Robin Burchell <robin.burchell@collabora.co.uk>
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

#include "common/debug/signal.h"
#include "common/debug/backtrace.h"

#include <QApplication>

#include "groovewindow.h"

#include "groove/client.h"
#include "groove/song.h"

static void
help ()
{
  printf ("Usage: %s\n", PACKAGE);
}

static void
version ()
{
  printf ("%s version %s\n\n", PACKAGE_NAME, PACKAGE_VERSION);
  puts ("Copyright © 2010 Robin Burchell <robin.burchell@collabora.co.uk>");
  puts ("Copyright © 2010 Pippijn van Steenhoven <pippijn@xinutec.org>");
  puts ("");
  puts ("This program is free software; you can redistribute it and/or modify it");
  puts ("under the terms and conditions of the GNU Lesser General Public License,");
  puts ("version 2.1, as published by the Free Software Foundation.");
}

static backtrace_status_fn print_status;
static void
print_status (size_t cur, size_t max)
{
  fprintf (stdout, "\r==%d== building stack trace: %zu%% (%zu / %zu)", getpid (), cur * 100 / max, cur, max);
  fflush (stdout);
  if (cur == max)
    fputc ('\n', stdout);
}

#include <sys/resource.h>

static void
limit ()
{
  // 512MiB address space
  {
    struct rlimit const rlim = {
      512 * 1024 * 1024,
      512 * 1024 * 1024,
    };
    setrlimit (RLIMIT_AS, &rlim);
  }
  // 8MiB stack
  {
    struct rlimit const rlim = {
      8 * 1024 * 1024,
      8 * 1024 * 1024,
    };
    setrlimit (RLIMIT_STACK, &rlim);
  }
}

int
main (int argc, char **argv)
{
  init_signals ();
  backtrace_status = print_status;

  QApplication qca (argc, argv);

  qca.setOrganizationName ("Xinutec");
  qca.setApplicationName ("Groovy");

  QStringList args = qca.arguments ();

  if (args.contains ("--help"))
    return help (), EXIT_SUCCESS;
  if (args.contains ("--version"))
    return version (), EXIT_SUCCESS;

  MainWindow mw;
  mw.show ();

  int retval = qca.exec ();

  uninit_signals ();

  return retval;
}
