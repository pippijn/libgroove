/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

#include "groove/songptr.h"
class GrooveClient;
class GrooveService;

#include <QFile>
class QNetworkReply;

#include <memory>

class LIBGROOVESHARED_EXPORT GrooveFetcher
  : public QObject
{
  Q_OBJECT

  QFile m_file;
  GrooveSongPointer m_song;
  bool m_nowStreaming;
  std::shared_ptr<GrooveClient> m_client;

public:
  QString name () const;
  QString fileName () const;
  bool streaming () const;

public:
  GrooveFetcher (GrooveSongPointer song, std::shared_ptr<GrooveClient> client);
  ~GrooveFetcher ();
  void fetch (GrooveService &service);

private slots:
  void onStreamKeyReady (QString ip, QString streamKey);
  void onStreamingStarted (QNetworkReply *);
  void onStreamReadReady ();
  void onStreamingFinished ();

signals:
  void songReady ();
};
