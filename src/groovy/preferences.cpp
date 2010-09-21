/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

#include <boost/foreach.hpp>

#include "groove/client.h"
#include "grooveplaylistmodel.h"
#include "groovesearchmodel.h"
#include "groove/settings.h"
#include "groove/song.h"

#include "preferences.h"
#include "ui_preferences.h"

static struct property
{
  char const *prop;
  char const *name;
} const song_properties[] = {
  { "songName",                 "Title"         },
  { "albumName",                "Album"         },
  { "artistName",               "Artist"        },
  { "year",                     "Year"          },
  { "trackNum",                 "Track"         },
  { "estimateDuration",         "Duration (s)"  },
  { "estimateDurationMins",     "Duration"      },
  { "popularity",               "Popularity"    },
  { "songPlays",                "Plays"         },
  { "songClicks",               "Clicks"        },
  { "score",                    "Score"         },
  { "rank",                     "Rank"          },
};

Preferences::Preferences (GrooveSearchModel &searchModel, GroovePlaylistModel &playListModel, QWidget *parent)
  : QDialog (parent)
  , m_ui (new Ui::Preferences)
  , m_searchModel (searchModel)
  , m_playListModel (playListModel)
{
  m_ui->setupUi (this);

  BOOST_FOREACH (auto const &prop, song_properties)
    {
      QListWidgetItem *item;

      item = new QListWidgetItem (prop.name, m_ui->lstSearchItems);
      item->setData (Qt::UserRole, prop.prop);
      item->setSelected (m_searchModel.isVisible (prop.prop));
      m_ui->lstSearchItems->addItem (item);

      item = new QListWidgetItem (prop.name, m_ui->lstPlaylistItems);
      item->setData (Qt::UserRole, prop.prop);
      item->setSelected (m_playListModel.isVisible (prop.prop));
      m_ui->lstPlaylistItems->addItem (item);
    }

  QSettings settings;

  m_ui->txtCachePath->setText (settings.value (GrooveSettings::CACHEDIR).toString ());
}

Preferences::~Preferences ()
{
}

void
Preferences::commitGeneral ()
{
  QSettings settings;
  
  if (QFile::exists (m_ui->txtCachePath->text ()))
    settings.setValue (GrooveSettings::CACHEDIR, m_ui->txtCachePath->text ());
  else
    QMessageBox::warning (this,
                          tr ("Invalid path"),
                          tr ("invalid path: ") + m_ui->txtCachePath->text ());
}

void
Preferences::commitVisibleRows ()
{
  m_searchModel.beginChangeVisible ();
  foreach (QListWidgetItem *item, m_ui->lstSearchItems->selectedItems ())
    {
      GROOVE_VERIFY_OR_DIE (item->data (Qt::UserRole).canConvert<QString> (), "invalid user data in list item");
      QString prop = item->data (Qt::UserRole).value<QString> ();
      m_searchModel.addVisible (prop);
    }
  m_searchModel.endChangeVisible ();

  m_playListModel.beginChangeVisible ();
  foreach (QListWidgetItem *item, m_ui->lstPlaylistItems->selectedItems ())
    {
      GROOVE_VERIFY_OR_DIE (item->data (Qt::UserRole).canConvert<QString> (), "invalid user data in list item");
      QString prop = item->data (Qt::UserRole).value<QString> ();
      m_playListModel.addVisible (prop);
    }
  m_playListModel.endChangeVisible ();
}

void
Preferences::buttonBoxClicked (QAbstractButton *btn)
{
  bool closing = false;

  switch (m_ui->buttonBox->buttonRole (btn))
    {
    case QDialogButtonBox::RejectRole:
      closing = true;
      break;
    case QDialogButtonBox::AcceptRole:
      closing = true;
    case QDialogButtonBox::ApplyRole:
      commitGeneral ();
      commitVisibleRows ();
      break;
    default:
      GROOVE_VERIFY_OR_DIE (false, "invalid button role");
    }

  if (closing)
    close ();
}

void
Preferences::editCachePath ()
{
  QFileDialog chooser (this);

  chooser.setFileMode (QFileDialog::Directory);
  chooser.setOption (QFileDialog::ShowDirsOnly);
  
  chooser.exec ();

  m_ui->txtCachePath->setText (chooser.selectedFiles ()[0]);
}
