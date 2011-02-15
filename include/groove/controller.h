/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include <memory>

#include <QObject>

#include "libgroove_global.h"

class GrooveSearchModel;

class LIBGROOVESHARED_EXPORT GrooveController
  : public QObject
{
  Q_OBJECT

public:
  explicit GrooveController (QObject *parent = 0);
  ~GrooveController ();

  GrooveSearchModel &searchModel ();

public slots:
  void search (QString const &query);
  void autocomplete (QString const &query);

private slots:
  void connectionEstablished ();
  virtual void updateCompletion (QStringList const &artistList) = 0;

private:
  struct Private;
  std::shared_ptr<Private> self;
};
