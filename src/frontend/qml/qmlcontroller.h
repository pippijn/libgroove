/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

class QDeclarativeView;

#include "groove/controller.h"

class QmlController
  : public GrooveController
{
  Q_OBJECT

public:
  explicit QmlController (QDeclarativeView &view, QObject *parent = 0);
  ~QmlController ();

private:
  void updateCompletion (QStringList const &artistList);

private:
  QDeclarativeView &m_view;
};
