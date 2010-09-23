/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "libgroove_global.h"

#include <QDebug>
#include <QImage>
#include <QPixmap>

#include "about.h"
#include "ui_about.h"

About::About (QWidget *parent)
  : QDialog (parent)
  , m_ui (new Ui::About)
{
  m_ui->setupUi (this);

  QImage image (PKGDATADIR "/grooveshark-icon.png");
  GROOVE_VERIFY_OR_DIE (!image.isNull (), "could not load grooveshark logo");

  m_ui->lblImage->setPixmap (QPixmap::fromImage (image));
}

About::~About ()
{
}
