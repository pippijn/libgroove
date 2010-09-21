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

#include "groovewindow.h"

#include "groove/client.h"
#include "groove/song.h"

#include <QApplication>

#include <log4cpp/OstreamAppender.hh>

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
  puts ("under the terms and conditions of the GNU Lesser General Public License,");
  puts ("version 2.1, as published by the Free Software Foundation.");
}

extern void init_debuglib ();
extern void uninit_debuglib ();

int
main (int argc, char **argv)
{
  auto app = new log4cpp::OstreamAppender ("stdout", &std::cerr);
  auto layout = new log4cpp::BasicLayout;
  app->setLayout (layout);
  llog.setPriority (DEBUG);
  llog.setAppender (app);

  llog << DEBUG << "initialising...";

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

  MainWindow mw;
  mw.show ();

  int retval = qca.exec ();

  // uninitialise unportable debug library
  uninit_debuglib ();

  llog << DEBUG << "terminating...";

  return retval;
}
