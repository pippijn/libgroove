#include <QApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeView>

int
main (int argc, char **argv)
{
  QApplication qca (argc, argv);

  qca.setApplicationName ("Groovy");

  QDeclarativeView view;
  view.setSource (QUrl ("qrc:/views/mainwindow.qml"));
  view.show ();

  qca.exec ();
}
