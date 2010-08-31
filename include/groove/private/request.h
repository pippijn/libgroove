/*
 * Copyright © 2010 Robin Burchell <robin.burchell@collabora.co.uk>
 * Copyright © 2010 Pippijn van Steenhoven <pippijn@xinutec.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 2.1, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include "libgroove_global.h"

#include "groove/private/make_varmap.h"

#include "groove/client.h"

#include <QNetworkRequest>
#include <QNetworkReply>

#include <qjson/serializer.h>

struct LIBGROOVESHARED_EXPORT GrooveRequest
{
  GrooveRequest (GrooveRequest const &rhs) = delete;
  GrooveRequest &operator = (GrooveRequest const &rhs) = delete;

  static QString const API_URL;
  static QString const ART_BASE_URL;
  static QString const LOGIN_URL;

  static QString more (QString const &method)
  {
    return API_URL + "more.php?" + method;
  }

  static QString service ()
  {
    return API_URL + "service.php";
  }

  static QString stream (QString const &ip)
  {
    return "http://" + ip + "/stream.php";
  }

  explicit GrooveRequest (GrooveClient &client, QString service)
    : m_req (QUrl (service))
    , m_client (client)
    , m_jlist ()
  {
  }

  void post (QObject const *receiver, char const *slot)
  {
    m_req.setHeader (m_req.ContentTypeHeader, "application/json");

    QJson::Serializer serializer;
    QNetworkReply *reply = m_client.networkManager ().post (m_req, serializer.serialize (m_jlist));
    receiver->connect (reply, SIGNAL (finished ()), slot);
  }

  void get (QObject const *receiver, char const *slot)
  {
    m_req.setHeader (m_req.ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply *reply = m_client.networkManager ().get (m_req);
    receiver->connect (reply, SIGNAL (finished ()), slot);
  }

  QNetworkRequest m_req;
  GrooveClient &m_client;
  QVariantMap m_jlist;
};

static inline void
operator << (GrooveRequest &request, QVariantOrMap::map const &init)
{
  request.m_jlist << init;
}
