#pragma once

#include <memory>

#include <QObject>

class GrooveSearchModel;

class Controller
  : public QObject
{
  Q_OBJECT

public:
  explicit Controller (QObject *parent = 0);
  ~Controller ();

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
