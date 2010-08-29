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

#include <QMainWindow>
#include <QMap>
class QModelIndex;

#include <phonon/phonon>

class GrooveSearchModel;
class GroovePlaylistModel;
class GrooveSong;
class GrooveClient;
class Fetcher;

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

  void onBtnPrev ();
  void onBtnPause ();
  void onBtnNext ();

public:
  void initiatePlay ();

private:
  Fetcher *fetchPrevSong ();
  Fetcher *fetchNextSong ();
  Fetcher *fetchSong (GrooveSong *song);
  void playSong (Fetcher *fetcher, bool change = false);

  bool checkConnection () const;

  void initGroove ();
  void initSearch ();
  void initPlaylist ();
  void initPlayControls ();
  void initSlider ();

private:
  Ui::MainWindow *m_ui;
  GrooveClient *m_client;
  GrooveSearchModel *m_searchModel;
  GroovePlaylistModel *m_playlistModel;
  Phonon::MediaObject *m_mediaObject;
  QMap<QString, Fetcher *> m_fetchers;
  Fetcher *m_next;

  int m_seekTime;

  bool m_connected;
};

#endif /* MAINWINDOW_H */
