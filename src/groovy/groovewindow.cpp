#define LIVE 1

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

#include "ui_groovewindow.h"

#include "about.h"
#include "groovewindow.h"
#include "preferences.h"

#include "groove/client.h"
#include "groove/fetcher.h"
#include "grooveplaylistmodel.h"
#include "groovesearchmodel.h"
#include "groove/service.h"
#include "groove/settings.h"
#include "groove/data/song.h"

#include <phonon/AudioOutput>
#include <phonon/MediaObject>
#include <phonon/MediaSource>

#include <QMessageBox>
#include <QSettings>
#include <QTime>

#include <functional>

GrooveWindow::GrooveWindow (QWidget *parent)
  : QMainWindow (parent)
  , m_ui (new Ui::GrooveWindow)
  , m_client (new GrooveClient (this))
  , m_service (new GrooveService (m_client, "(null)", this))
  , m_searchModel (new GrooveSearchModel (m_client, this))
  , m_playlistModel (new GroovePlaylistModel (m_client, this))
  , m_mediaObject (new Phonon::MediaObject (this))
  , m_fetchers ()
  , m_next ()
  , m_seekTime (-1)
  , m_connected (false)
{
  m_ui->setupUi (this);

  Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput (Phonon::MusicCategory, this);
  Phonon::createPath (m_mediaObject.get (), audioOutput);

  initGroove ();
  initSearch ();
  initPlaylist ();
  initPlayControls ();
  initSlider ();

  connect (m_mediaObject.get (), SIGNAL (finished ()), SLOT (playNextSong ()));
  connect (m_mediaObject.get (), SIGNAL (currentSourceChanged (const Phonon::MediaSource &)), SLOT (onMediaChanged (Phonon::MediaSource const &)));

#if 0
  m_mediaObject->enqueue (Phonon::MediaSource ("/home/mpd/music/albums/Tool/2000 - Salival/07 - Tool - No Quarter.flac"));
  m_mediaObject->play ();
#endif
}

GrooveWindow::~GrooveWindow ()
{
}

void
GrooveWindow::changeEvent (QEvent *e)
{
  QMainWindow::changeEvent (e);
  switch (e->type ())
    {
    case QEvent::LanguageChange:
      m_ui->retranslateUi (this);
      break;
    default:
      break;
    }
}

void
GrooveWindow::onMediaChanged (Phonon::MediaSource const &newSource)
{
  LDEBUG << "Now playing: " << newSource.fileName ();
  m_ui->statusbar->showMessage (newSource.fileName ());
}

void
GrooveWindow::openPrefs ()
{
  Preferences prefs (*m_searchModel, *m_playlistModel, this);
  prefs.exec ();
}

void
GrooveWindow::openAbout ()
{
  About about (this);
  about.exec ();
}

template<typename T>
inline auto
GrooveWindow::switchSong (T action)
    -> decltype (action ())
{
  struct scoped_action
  {
    scoped_action (std::function<void ()> action)
      : m_action (action)
    {
    }
  
    ~scoped_action ()
    {
      m_action ();
    }
  
    std::function<void ()> m_action;
  };

  auto setter = [=] (QVariant const &value = QVariant ())
  {
    m_playlistModel->setData (m_playlistModel->index (m_playlistModel->currentTrack (), 0),
                              value, Qt::BackgroundColorRole);
  };
  // reset colour of current track to normal
  setter ();
  // set colour of next track to green (after `action' was performed)
  scoped_action sa { [setter] { setter (QColor (Qt::green)); } };
  return action ();
}

std::shared_ptr<GrooveFetcher>
GrooveWindow::fetchNextSong ()
{
  return switchSong ([=] { return fetchSong (m_playlistModel->next ()); });
}

std::shared_ptr<GrooveFetcher>
GrooveWindow::fetchPrevSong ()
{
  return switchSong ([=] { return fetchSong (m_playlistModel->previous ()); });
}

std::shared_ptr<GrooveFetcher>
GrooveWindow::fetchSong (GrooveSongPointer song)
{
  if (song == NULL)
    return { };

  std::shared_ptr<GrooveFetcher> fetcher;

  if (m_fetchers.find (song->songID ()) == m_fetchers.end ())
    (fetcher = m_fetchers[song->songID ()] = std::make_shared<GrooveFetcher> (song, m_client))->fetch (*m_service);
  else
    (fetcher = m_fetchers[song->songID ()]);

  GROOVE_VERIFY_OR_DIE (fetcher, "NULL fetcher in fetcher map");

  return fetcher;
}

void
GrooveWindow::playSong (std::shared_ptr<GrooveFetcher> fetcher, bool change)
{
  if (!fetcher)
    return;

  if (m_next)
    disconnect (m_next.get (), SIGNAL (songReady ()), this, SLOT (playCurrentSong ()));

  if (!fetcher->streaming ())
    {
      resetSlider ();

      if (change)
        {
          m_mediaObject->clearQueue ();
          m_mediaObject->setCurrentSource (Phonon::MediaSource (fetcher->fileName ()));
        }
      else
        {
          m_mediaObject->enqueue (Phonon::MediaSource (fetcher->fileName ()));
        }
      m_mediaObject->play ();
      m_next.reset ();
    }
  else
    {
      LDEBUG << "postponed playpack of " << fetcher->name ();
      connect (fetcher.get (), SIGNAL (songReady ()), SLOT (playCurrentSong ()));
      m_next = fetcher;
    }
}

void
GrooveWindow::playCurrentSong ()
{
  if (GROOVE_VERIFY (m_next, "no song to play"))
    return;
  LDEBUG << "now starting postponed playback of " << m_next->name ();
  playSong (m_next);
}

void
GrooveWindow::playNextSong ()
{
  LDEBUG << "phonon playlist finished, playing next song";
  playSong (fetchNextSong (), true);
}


//////////////////////////////////////////////////////////////////////////////
//                                groove                                    //
//////////////////////////////////////////////////////////////////////////////

inline void
GrooveWindow::initGroove ()
{
  m_ui->btnSearch->setEnabled (false);
  m_ui->statusbar->showMessage ("Establishing connection...");
#if LIVE
  m_client->establishConnection ();
#endif
  connect (m_client.get (), SIGNAL (connected ()), SLOT (onConnected ()));
}


void
GrooveWindow::onConnected ()
{
  m_connected = true;
  m_ui->btnSearch->setEnabled (true);
  m_ui->statusbar->showMessage ("Connection established");
}


//////////////////////////////////////////////////////////////////////////////
//                             playcontrols                                 //
//////////////////////////////////////////////////////////////////////////////

inline void
GrooveWindow::initPlayControls ()
{
}

void
GrooveWindow::onBtnPrev ()
{
  playSong (fetchPrevSong (), true);
}

void
GrooveWindow::onBtnPause ()
{
  if (m_mediaObject->state () == Phonon::PausedState)
    m_mediaObject->play ();
  else
    m_mediaObject->pause ();
}

void
GrooveWindow::onBtnNext ()
{
  playSong (fetchNextSong (), true);
}


//////////////////////////////////////////////////////////////////////////////
//                               playlist                                   //
//////////////////////////////////////////////////////////////////////////////

inline void
GrooveWindow::initPlaylist ()
{
  m_ui->tblPlaylistView->setModel (m_playlistModel.get ());
  connect (m_ui->tblPlaylistView, SIGNAL (doubleClicked (QModelIndex)), SLOT (onPlaySong (QModelIndex)));
}

void
GrooveWindow::onPlaySong (QModelIndex const &index)
{
  GrooveSongPointer song = switchSong ([=] () -> GrooveSongPointer { return m_playlistModel->select (index); });

  LDEBUG << "Playing " << song->songName ();

  playSong (fetchSong (song), true);
}


//////////////////////////////////////////////////////////////////////////////
//                                search                                    //
//////////////////////////////////////////////////////////////////////////////

inline void
GrooveWindow::initSearch ()
{
  m_ui->tblSearchResults->setModel (m_searchModel.get ());
}

void
GrooveWindow::onQueueSong (QModelIndex const &index)
{
  GrooveSongPointer song = m_searchModel->songByIndex (index);

  LDEBUG << "Queueing " << song->songName ();

  m_playlistModel->append (song);
  std::shared_ptr<GrooveFetcher> fetcher = fetchSong (song);
  if (!m_next && m_mediaObject->state () != Phonon::PlayingState)
    switchSong ([=] { playSong (fetchSong (m_playlistModel->last ())); });
}

void
GrooveWindow::onSearchButtonPress ()
{
  if (!checkConnection ())
    return;
  LDEBUG << "Searching for " << m_ui->txtSearch->text ();
  m_searchModel->searchBySong (m_ui->txtSearch->text ());
}

inline bool
GrooveWindow::checkConnection () const
{
  if (!m_connected)
    {
      QMessageBox::information (NULL, "Not Connected", "Groovy is not connected, please wait for the session token.");
      return false;
    }
  return true;
}


//////////////////////////////////////////////////////////////////////////////
//                                slider                                    //
//////////////////////////////////////////////////////////////////////////////

static int const tickInterval = 1000; // msec

inline void
GrooveWindow::initSlider ()
{
  m_mediaObject->setTickInterval (tickInterval);

  connect (m_mediaObject.get (), SIGNAL (tick (qint64)), SLOT (songTick (qint64)));
  connect (m_mediaObject.get (), SIGNAL (totalTimeChanged (qint64)), SLOT (songTotalTimeChanged (qint64)));
}


void
GrooveWindow::beginSeekSong (int time)
{
  m_seekTime = time;
  m_ui->lblElapsed->setText (QTime ().addSecs (time / tickInterval).toString ("m:ss"));
}

void
GrooveWindow::endSeekSong ()
{
  m_mediaObject->seek (m_seekTime);
  m_seekTime = -1;
}

void
GrooveWindow::songTick (qint64 time)
{
  if (m_seekTime == -1)
    {
      m_ui->songProgress->setValue (time);
      m_ui->lblElapsed->setText (QTime ().addSecs (time / tickInterval).toString ("m:ss"));
    }
}

void
GrooveWindow::songTotalTimeChanged (qint64 newTotalTime)
{
  m_ui->songProgress->setMaximum (newTotalTime);
  m_ui->lblTotal->setText (QTime ().addSecs (newTotalTime / tickInterval).toString ("m:ss"));
}

void
GrooveWindow::resetSlider ()
{
  songTotalTimeChanged (0);
  songTick (0);
}
