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

#include "groove/private/make_varmap.h"

#include "groove/client.h"

#include <QNetworkRequest>
#include <QNetworkReply>

#include <qjson/serializer.h>

struct GrooveRequest
{
  explicit GrooveRequest (GrooveClient &client, QString service, QString method = QString ())
    : m_req (QUrl ("https://cowbell.grooveshark.com/" + service))
    , m_client (client)
  {
    m_req.setHeader (m_req.ContentTypeHeader, "application/json");
  }

  void post (QObject *receiver, char const *slot)
  {
    QJson::Serializer serializer;
    QNetworkReply *reply = m_client.networkManager ().post (m_req, serializer.serialize (jlist));
    receiver->connect (reply, SIGNAL (finished ()), slot);
  }

  QNetworkRequest m_req;
  GrooveClient &m_client;
  QVariantMap jlist;
};

static inline void
operator << (GrooveRequest &request, QVariantOrMap::map const &init)
{
  request.jlist << init;
}
