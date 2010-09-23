/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
class GrooveSearchModel;
class GroovePlaylistModel;

#include <QDialog>
class QAbstractButton;

#include <memory>

namespace Ui
{
  class Preferences;
}

class Preferences
  : public QDialog
{
  Q_OBJECT

  void *operator new (size_t) = delete;

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
  std::auto_ptr<Ui::Preferences> m_ui;
  GrooveSearchModel &m_searchModel;
  GroovePlaylistModel &m_playListModel;
};
