/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include <QDialog>

#include <memory>

namespace Ui
{
  class About;
}

class About
  : public QDialog
{
  Q_OBJECT

  void *operator new (size_t) = delete;

public:
  About (QWidget *parent);
  ~About ();

private:
  std::auto_ptr<Ui::About> m_ui;
};
