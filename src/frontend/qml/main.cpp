/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include <QApplication>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QNetworkProxy>

#include "groove/searchmodel.h"

#include "qmlcontroller.h"

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

  // View
  QDeclarativeView view;

  // Controller
  QmlController controller (view);

  // Linking model and view
  QDeclarativeContext *context = view.rootContext ();
  context->setContextProperty ("controller", &controller);
  context->setContextProperty ("searchModel", &controller.searchModel ());

  // Load UI description into view
  view.setSource (QUrl ("qrc:/views/mainwindow.qml"));

  // Run the application
  view.show ();
  qca.exec ();
}
