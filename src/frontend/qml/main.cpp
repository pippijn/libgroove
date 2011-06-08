/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "config.h"

#include <QApplication>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QNetworkProxy>

#include "groove/playlistmodel.h"
#include "groove/searchmodel.h"

#include "qmlcontroller.h"

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


static void
setupProxy (QString hostName, quint16 port, QString user, QString password)
{
  QNetworkProxy proxy;
  proxy.setType (QNetworkProxy::Socks5Proxy);
  proxy.setHostName (hostName);
  proxy.setPort (port);
  proxy.setUser (user);
  proxy.setPassword (password);
  QNetworkProxy::setApplicationProxy (proxy);
}


int
main (int argc, char **argv)
{
  QApplication qca (argc, argv);

  qca.setApplicationName ("Groovy");

  QStringList args = qca.arguments ();
  if (args.contains ("--proxy"))
    setupProxy ("localhost", 8080, "username", "password");

  if (args.contains ("--help"))
    return help (), EXIT_SUCCESS;
  if (args.contains ("--version"))
    return version (), EXIT_SUCCESS;

  // View
  QDeclarativeView view;
  view.setResizeMode (QDeclarativeView::SizeRootObjectToView);

  // Controller
  QmlController controller (view);

  // Linking model and view
  QDeclarativeContext *context = view.rootContext ();
  context->setContextProperty ("controller", &controller);
  context->setContextProperty ("searchModel", &controller.searchModel ());
  context->setContextProperty ("playlistModel", &controller.playlistModel ());

  // Load UI description into view
  view.setSource (QUrl ("qrc:/views/mainwindow.qml"));

  // Allow QML application to quit the entire application
  QObject::connect (view.engine (), SIGNAL (quit ()), &qca, SLOT (quit ()));

  // Run the application
  view.show ();
  qca.exec ();
}
