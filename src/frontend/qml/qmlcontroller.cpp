/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QStringList>

#include "qmlcontroller.h"

QmlController::QmlController (QDeclarativeView &view, QObject *parent)
  : GrooveController (parent)
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
