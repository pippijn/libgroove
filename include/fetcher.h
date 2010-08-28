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
  GrooveSong &m_song;
  bool m_nowStreaming;

public:
  QString fileName () const;
  bool streaming () const;

public:
  Fetcher (GrooveSong &song);
  ~Fetcher ();
  void fetch ();

private slots:
  void onStreamingStarted (QNetworkReply *);
  void onStreamReadReady ();
  void onStreamingFinished ();

signals:
  void songReady ();
};
