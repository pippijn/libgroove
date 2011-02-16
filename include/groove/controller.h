/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include <memory>

#include <QObject>

#include "libgroove_global.h"

class GroovePlaylistModel;
class GrooveSearchModel;

class LIBGROOVESHARED_EXPORT GrooveController
  : public QObject
{
  Q_OBJECT

public:
  explicit GrooveController (QObject *parent = 0);
  ~GrooveController ();

  GroovePlaylistModel &playlistModel ();
  GrooveSearchModel &searchModel ();

public slots:
  // Initiates a search and updates the search model.
  void search (QString const &query);
  // Starts playing the song at index from the playlist model.
  void play (int index);
  // Copies the song at index from the search model to the playlist model.
  void enqueue (int index);
  // Removes the song at index from the playlist model.
  void unqueue (int index);
  // Initiates an autocompletion request. Results will be published with updateCompletion.
  void autocomplete (QString const &query);

private slots:
  void connectionEstablished ();
  // Overridden by derived classes to get the results from an autocomplete call.
  virtual void updateCompletion (QStringList const &artistList) = 0;

private:
  struct Private;
  std::shared_ptr<Private> self;
};
