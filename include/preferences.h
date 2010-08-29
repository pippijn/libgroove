/*
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

#include <QDialog>
class QAbstractButton;

class GrooveSearchModel;
class GroovePlaylistModel;

namespace Ui
{
  class Preferences;
}

class Preferences
  : public QDialog
{
  Q_OBJECT

public:
  Preferences (GrooveSearchModel &searchModel, GroovePlaylistModel &playListModel, QWidget *parent);
  ~Preferences ();

private:
  void commitGeneral ();
  void commitVisibleRows ();

private slots:
  void buttonBoxClicked (QAbstractButton *btn);
  void editCachePath ();

private:
  Ui::Preferences *m_ui;
  GrooveSearchModel &m_searchModel;
  GroovePlaylistModel &m_playListModel;
};
