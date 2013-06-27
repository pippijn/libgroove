/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#include "libgroove_global.h"

#include "property.h"

#include <QString>
#include <QSettings>

#define SETTING_CACHEDIR "cachedir"

struct LIBGROOVESHARED_EXPORT GrooveSettings
{
  struct section
  {
    static QString const PLAYLIST;
    static QString const SEARCH;
  };

  static QString const COLUMNS;

  def_prop (QString, GrooveSettings, cachedir,
    {
      return QSettings ().value (SETTING_CACHEDIR, "cache").toString ();
    },
    {
      QSettings ().setValue (SETTING_CACHEDIR, value);
    }
  );
};

extern LIBGROOVESHARED_EXPORT GrooveSettings Settings;
