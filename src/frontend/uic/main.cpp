/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "frontend/uic/groovewindow.h"

#include "groove/client.h"
#include "groove/data/song.h"

#include <QApplication>

#include <iostream>

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
  puts ("under the terms and conditions of the GNU Affero General Public License,");
  puts ("version 3, as published by the Free Software Foundation, or later.");
  puts ("");
  printf ("Send bugreports to %s\n", PACKAGE_BUGREPORT);
}

extern void init_debuglib ();
extern void uninit_debuglib ();

int
main (int argc, char **argv)
{
  // initialise the unportable debug library
  init_debuglib ();

  // now start the portable Qt code
  QApplication qca (argc, argv);

  qca.setOrganizationName ("Xinutec");
  qca.setApplicationName ("Groovy");

  QStringList args = qca.arguments ();

  if (args.contains ("--help"))
    return help (), EXIT_SUCCESS;
  if (args.contains ("--version"))
    return version (), EXIT_SUCCESS;

  LDEBUG << "initialising...";

  GrooveWindow mw;
  mw.show ();

  int retval = qca.exec ();

  // uninitialise unportable debug library
  uninit_debuglib ();

  LDEBUG << "terminating...";

  return retval;
}
