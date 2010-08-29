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

#include <QDebug>
#include <QMessageBox>
#include <QSettings>
#include <QTime>

#include "groove/client.h"
#include "groove/fetcher.h"
#include "grooveplaylistmodel.h"
#include "groovesearchmodel.h"
#include "groove/song.h"

#include "about.h"
#include "groovewindow.h"
#include "preferences.h"

#include "ui_groovewindow.h"

MainWindow::MainWindow (QWidget *parent)
  : QMainWindow (parent)
  , m_ui (new Ui::MainWindow)
  , m_client (new GrooveClient (this))
  , m_searchModel (new GrooveSearchModel (*m_client, this))
  , m_playlistModel (new GroovePlaylistModel (*m_client, this))
  , m_mediaObject (new Phonon::MediaObject (this))
  , m_next (0)
  , m_seekTime (-1)
  , m_connected (false)
{
  m_ui->setupUi (this);

  Phonon::AudioOutput *audioOutput = new Phonon::AudioOutput (Phonon::MusicCategory, this);
  Phonon::createPath (m_mediaObject, audioOutput);


  initGroove ();
  initSearch ();
  initPlaylist ();
  initPlayControls ();
  initSlider ();

  connect (m_mediaObject, SIGNAL (finished ()), SLOT (playNextSong ()));
  connect (m_mediaObject, SIGNAL (currentSourceChanged (const Phonon::MediaSource &)), SLOT (onMediaChanged (Phonon::MediaSource const &)));

  //m_mediaObject->enqueue (Phonon::MediaSource ("cache/Nine Inch Nails/With Teeth/Every Day Is Exactly the Same.mp3"));
  //m_mediaObject->play ();
}

MainWindow::~MainWindow ()
{
  delete m_ui;
}

void
MainWindow::changeEvent (QEvent *e)
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
MainWindow::onMediaChanged (Phonon::MediaSource const &newSource)
{
  qDebug () << Q_FUNC_INFO << "Now playing:" << newSource.fileName ();
  m_ui->statusbar->showMessage (newSource.fileName ());
}

void
MainWindow::openPrefs ()
{
  Preferences prefs (*m_searchModel, *m_playlistModel, this);
  prefs.exec ();
}

void
MainWindow::openAbout ()
{
  About about (this);
  about.exec ();
}

GrooveFetcher *
MainWindow::fetchNextSong ()
{
  return fetchSong (m_playlistModel->next ());
}

GrooveFetcher *
MainWindow::fetchPrevSong ()
{
  return fetchSong (m_playlistModel->previous ());
}

GrooveFetcher *
MainWindow::fetchSong (GrooveSong *song)
{
  if (song == NULL)
    return NULL;

  GrooveFetcher *fetcher = NULL;

  if (m_fetchers.contains (song->songID ()))
    fetcher = m_fetchers[song->songID ()];
  else
    (fetcher = m_fetchers[song->songID ()] = new GrooveFetcher (*song))->fetch ();

  GROOVE_VERIFY_OR_DIE (fetcher, "NULL fetcher in fetcher map");

  return fetcher;
}

void
MainWindow::playSong (GrooveFetcher *fetcher, bool change)
{
  if (!fetcher)
    return;

  if (m_next)
    disconnect (m_next, SIGNAL (songReady ()), this, SLOT (playCurrentSong ()));

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
      m_next = NULL;
    }
  else
    {
      qDebug () << Q_FUNC_INFO << "postponed playpack of" << fetcher->name ();
      connect (fetcher, SIGNAL (songReady ()), this, SLOT (playCurrentSong ()));
      m_next = fetcher;
    }
}

void
MainWindow::playCurrentSong ()
{
  if (GROOVE_VERIFY (m_next, "no song to play"))
    return;
  qDebug () << Q_FUNC_INFO << "now starting postponed playback of" << m_next->name ();
  playSong (m_next);
}

void
MainWindow::playNextSong ()
{
  qDebug () << Q_FUNC_INFO << "phonon playlist finished, playing next song";
  playSong (fetchNextSong (), true);
}


//////////////////////////////////////////////////////////////////////////////
//                                groove                                    //
//////////////////////////////////////////////////////////////////////////////

inline void
MainWindow::initGroove ()
{
  m_ui->statusbar->showMessage ("Establishing connection...");
#if LIVE
  m_client->establishConnection ();
#endif
  connect (m_client, SIGNAL (connected ()), SLOT (onConnected ()));
}


void
MainWindow::onConnected ()
{
  m_connected = true;
  m_ui->statusbar->showMessage ("Connection established");
}


//////////////////////////////////////////////////////////////////////////////
//                             playcontrols                                 //
//////////////////////////////////////////////////////////////////////////////

inline void
MainWindow::initPlayControls ()
{
}

void
MainWindow::onBtnPrev ()
{
  playSong (fetchPrevSong (), true);
}

void
MainWindow::onBtnPause ()
{
  if (m_mediaObject->state () == Phonon::PausedState)
    m_mediaObject->play ();
  else
    m_mediaObject->pause ();
}

void
MainWindow::onBtnNext ()
{
  playSong (fetchNextSong (), true);
}


//////////////////////////////////////////////////////////////////////////////
//                               playlist                                   //
//////////////////////////////////////////////////////////////////////////////

inline void
MainWindow::initPlaylist ()
{
  m_ui->tblPlaylistView->setModel (m_playlistModel);
  connect (m_ui->tblPlaylistView, SIGNAL (doubleClicked (QModelIndex)), SLOT (onPlaySong (QModelIndex)));
}

void
MainWindow::onPlaySong (QModelIndex const &index)
{
  GrooveSong *song = m_playlistModel->select (index);

  qDebug () << Q_FUNC_INFO << "Playing" << song->songName ();

  playSong (fetchSong (song), true);
}


//////////////////////////////////////////////////////////////////////////////
//                                search                                    //
//////////////////////////////////////////////////////////////////////////////

inline void
MainWindow::initSearch ()
{
  m_ui->tblSearchResults->setModel (m_searchModel);
}

void
MainWindow::onQueueSong (QModelIndex const &index)
{
  GrooveSong *song = m_searchModel->songByIndex (index);

  qDebug () << Q_FUNC_INFO << "Queueing" << song->songName ();

  m_playlistModel->append (song);
  GrooveFetcher *fetcher = fetchSong (song);
  if (!m_next && m_mediaObject->state () != Phonon::PlayingState)
    playSong (fetchSong (m_playlistModel->last ()));
}

void
MainWindow::onSearchButtonPress ()
{
  if (!checkConnection ())
    return;
  qDebug () << Q_FUNC_INFO << "Searching for" << m_ui->txtSearch->text ();
  m_searchModel->searchBySong (m_ui->txtSearch->text ());
}

inline bool
MainWindow::checkConnection () const
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
MainWindow::initSlider ()
{
  m_mediaObject->setTickInterval (tickInterval);

  connect (m_mediaObject, SIGNAL (tick (qint64)), SLOT (songTick (qint64)));
  connect (m_mediaObject, SIGNAL (totalTimeChanged (qint64)), SLOT (songTotalTimeChanged (qint64)));
}


void
MainWindow::beginSeekSong (int time)
{
  m_seekTime = time;
  m_ui->lblElapsed->setText (QTime ().addSecs (time / tickInterval).toString ("m:ss"));
}

void
MainWindow::endSeekSong ()
{
  m_mediaObject->seek (m_seekTime);
  m_seekTime = -1;
}

void
MainWindow::songTick (qint64 time)
{
  if (m_seekTime == -1)
    {
      m_ui->songProgress->setValue (time);
      m_ui->lblElapsed->setText (QTime ().addSecs (time / tickInterval).toString ("m:ss"));
    }
}

void
MainWindow::songTotalTimeChanged (qint64 newTotalTime)
{
  m_ui->songProgress->setMaximum (newTotalTime);
  m_ui->lblTotal->setText (QTime ().addSecs (newTotalTime / tickInterval).toString ("m:ss"));
}

void
MainWindow::resetSlider ()
{
  songTotalTimeChanged (0);
  songTick (0);
}
