/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

#include "groove/songptr.h"

#include <QFile>
class QNetworkReply;

class LIBGROOVESHARED_EXPORT GrooveFetcher
  : public QObject
{
  Q_OBJECT

  QFile m_file;
  GrooveSongPointer m_song;
  bool m_nowStreaming;

public:
  QString name () const;
  QString fileName () const;
  bool streaming () const;

public:
  GrooveFetcher (GrooveSongPointer song);
  ~GrooveFetcher ();
  void fetch ();

private slots:
  void onStreamingStarted (QNetworkReply *);
  void onStreamReadReady ();
  void onStreamingFinished ();

signals:
  void songReady ();
};
