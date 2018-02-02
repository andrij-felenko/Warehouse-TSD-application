#ifndef SERVER_CACHE_SINGLE_H
#define SERVER_CACHE_SINGLE_H

#include <QtCore/QObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QDateTime>
#include "Enum/enum.h"

class ServerCacheSingle : public QObject
{
public:
    ServerCacheSingle(QObject* sender = nullptr, QString func_success = "",
                      QString id_request = "", QString url = "", QString id_msg = "",
                      QJsonDocument document = QJsonDocument(), QObject *parent = nullptr,
                      Enum::Request_priority priority = Enum::Request_priority_can_ignore)
        : QObject(parent), m_sender(sender), m_func_success(func_success),
          m_id_request(id_request), m_url(url), m_id_msg(id_msg), m_document(document),
          m_priority(priority), m_dtime(QDateTime::currentDateTime()), m_is_accept(false)
    {
        //
    }

    ServerCacheSingle(QObject* sender, QString func_success,
                      QString id_request, QString url, QString id_msg,
                      QObject *parent)
        : ServerCacheSingle(sender, func_success, id_request, url, id_msg, QJsonDocument(), parent)
    {
        //
    }

    QObject* sender() { return m_sender; }
    QString func_success() { return m_func_success; }
    QString id_request() { return m_id_request; }
    QString url() { return m_url; }
    QString id_msg() { return m_id_msg; }
    QJsonDocument document() { return m_document; }
    Enum::Request_priority priority() { return m_priority; }
    int secAfterRequest() { return m_dtime.secsTo(QDateTime::currentDateTime()); }
    QDateTime dateTime() { return m_dtime; }
    bool isAccept() { return m_is_accept; }
    void accept() { m_is_accept = true; }

private:
    QObject* m_sender;
    QString m_func_success;
    QString m_id_request;
    QString m_url;
    QString m_id_msg;
    QJsonDocument m_document;
    Enum::Request_priority m_priority;
    QDateTime m_dtime;
    bool m_is_accept;
};

#endif // SERVER_CACHE_SINGLE_H
