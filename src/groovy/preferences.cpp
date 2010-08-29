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

#include "groove/client.h"
#include "grooveplaylistmodel.h"
#include "groovesearchmodel.h"
#include "groove/song.h"

#include "preferences.h"
#include "ui_preferences.h"

Preferences::Preferences (QWidget *parent)
  : QDialog (parent)
  , m_ui (new Ui::Preferences)
{
  m_ui->setupUi (this);

  m_ui->lstSearchAvailable->addItem ("item1");
  m_ui->lstSearchAvailable->addItem ("item2");
  m_ui->lstSearchAvailable->addItem ("item3");
  m_ui->lstSearchAvailable->addItem ("item4");
  m_ui->lstSearchAvailable->addItem ("item5");
  m_ui->lstSearchAvailable->addItem ("item6");
  m_ui->lstSearchAvailable->addItem ("item7");
  m_ui->lstSearchAvailable->addItem ("item8");
  m_ui->lstSearchAvailable->addItem ("item9");
  m_ui->lstSearchAvailable->addItem ("item10");
  m_ui->lstSearchAvailable->addItem ("item11");
  m_ui->lstSearchAvailable->addItem ("item12");
  m_ui->lstSearchAvailable->addItem ("item13");
  m_ui->lstSearchAvailable->addItem ("item14");
}

Preferences::~Preferences ()
{
  delete m_ui;
}
