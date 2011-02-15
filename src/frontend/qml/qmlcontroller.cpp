#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QStringList>

#include "libgroove_global.h"

#include "qmlcontroller.h"

QmlController::QmlController (QDeclarativeView &view, QObject *parent)
  : Controller (parent)
  , m_view (view)
{
  QStringList dataList;
  dataList.append ("Item 1");
  dataList.append ("Item 2");
  dataList.append ("Item 3");
  dataList.append ("Item 4");
  dataList.append ("Item 5");
  updateCompletion (dataList);
}

QmlController::~QmlController ()
{
}


void
QmlController::updateCompletion (QStringList const &artistList)
{
  LDEBUG << "got autocomplete list:" << artistList;

  QDeclarativeContext *ctxt = m_view.rootContext ();
  ctxt->setContextProperty ("completion", artistList);
}
