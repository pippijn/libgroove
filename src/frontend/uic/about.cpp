/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "libgroove_global.h"

#include <QDebug>
#include <QImage>
#include <QPixmap>

#include "frontend/uic/about.h"
#include "ui_about.h"

About::About (QWidget *parent)
  : QDialog (parent)
  , m_ui (new Ui::About)
{
  m_ui->setupUi (this);
}

About::~About ()
{
}
