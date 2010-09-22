/* Copyright © 2010 Pippijn van Steenhoven
 * See COPYING.AGPL for licence information.
 */
#pragma once

#include "libgroove_global.h"

class GrooveClient;
class GrooveService;
class GrooveSong;

#include <QFile>
class QNetworkReply;

#include <memory>

class LIBGROOVESHARED_EXPORT GrooveFetcher
  : public QObject
{
  Q_OBJECT

  QFile m_file;
  bool m_nowStreaming;
  std::shared_ptr<GrooveClient> m_client;
  struct Song
  {
    QString const name;
    int const ID;
  } const m_song;

public:
  QString name () const;
  QString fileName () const;
  bool streaming () const;

public:
  GrooveFetcher (GrooveSong const &song, std::shared_ptr<GrooveClient> client);
  ~GrooveFetcher ();
  void fetch (GrooveService &service);

private slots:
  void onStreamKeyReady (QString ip, QString streamKey);
  void onStreamingStarted (QNetworkReply *httpStream);
  void onStreamReadReady ();
  void onStreamingFinished ();

signals:
  void songReady ();
};
