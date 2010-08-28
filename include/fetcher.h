#pragma once

#include <QFile>

class GrooveSong;
class QNetworkReply;
class MainWindow;

class Fetcher
  : public QObject
{
  Fetcher (Fetcher const &other) = delete;
  Fetcher &operator = (Fetcher const &rhs) = delete;

  Q_OBJECT

  QFile m_file;
  GrooveSong *m_song;
  MainWindow *m_parent;
  bool m_nowStreaming;

public:
  QString fileName () const;
  bool streaming () const;
  GrooveSong *song () const;

public:
  Fetcher (GrooveSong *song, MainWindow *parent);
  void fetch ();

private slots:
  void onStreamingStarted (QNetworkReply *);
  void onStreamReadReady ();
  void onStreamingFinished ();

signals:
  void songReady ();
};
