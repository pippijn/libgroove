#pragma once

class QDeclarativeView;

#include "controller.h"

class QmlController
  : public Controller
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
