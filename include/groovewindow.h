/*
 * Copyright © 2010 Robin Burchell <robin.burchell@collabora.co.uk>
 * Copyright © 2010 Pippijn van Steenhoven <pippijn@xinutec.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <map>

#include "groove/songptr.h"
class GrooveClient;
class GrooveFetcher;
class GroovePlaylistModel;
class GrooveSearchModel;

#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>

#include <QMainWindow>
class QModelIndex;

namespace Ui
{
  class MainWindow;
}

class MainWindow
  : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow (QWidget *parent = 0);
  ~MainWindow ();

protected:
  void changeEvent (QEvent *e);

private slots:
  void onConnected ();

  void onSearchButtonPress ();

  void onPlaySong (QModelIndex const &index);
  void onQueueSong (QModelIndex const &index);

  void beginSeekSong (int time);
  void endSeekSong ();
  void songTick (qint64 time);
  void songTotalTimeChanged (qint64 newTotalTime);

  void playCurrentSong ();
  void playNextSong ();
  
  void onMediaChanged (Phonon::MediaSource const &newSource);

  void openPrefs ();
  void openAbout ();

  void onBtnPrev ();
  void onBtnPause ();
  void onBtnNext ();
  
  void crash ();

public:
  void initiatePlay ();

private:
  template<typename T>
  auto switchSong (T action) -> decltype (action ());
  std::shared_ptr<GrooveFetcher> fetchPrevSong ();
  std::shared_ptr<GrooveFetcher> fetchNextSong ();
  std::shared_ptr<GrooveFetcher> fetchSong (GrooveSongPointer song);
  void playSong (std::shared_ptr<GrooveFetcher> fetcher, bool change = false);

  bool checkConnection () const;

  void initGroove ();
  void initSearch ();
  void initPlaylist ();
  void initPlayControls ();
  void initSlider ();

  void resetSlider ();

private:
  std::auto_ptr<Ui::MainWindow> m_ui;
  std::shared_ptr<GrooveClient> m_client;
  std::auto_ptr<GrooveSearchModel> m_searchModel;
  std::auto_ptr<GroovePlaylistModel> m_playlistModel;
  std::auto_ptr<Phonon::MediaObject> m_mediaObject;
  std::map<QString, std::shared_ptr<GrooveFetcher>> m_fetchers;
  std::shared_ptr<GrooveFetcher> m_next;

  int m_seekTime;

  bool m_connected;
};

#endif /* MAINWINDOW_H */
