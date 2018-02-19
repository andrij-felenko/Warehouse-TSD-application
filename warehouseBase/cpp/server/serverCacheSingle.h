#ifndef SERVER_CACHE_SINGLE_H
#define SERVER_CACHE_SINGLE_H

#include <QtCore/QObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QDateTime>
#include "enum/wenum.h"
#include "wjsonTemplate.h"

class ServerCacheSingle : public QObject
{
public:
    ServerCacheSingle(QObject* sender = nullptr, QString functionName = "",
                      QString url = "", QString id_msg = "",
                      QJsonValue json = QJsonValue(), QObject *parent = nullptr,
                      WEnum::Request_priority priority = WEnum::Request_just_info)
        : QObject(parent), m_sender(sender), m_functionName(functionName), m_id_msg(id_msg),
          m_json(new WJsonTemplate(url, json, this)), m_priority(priority), m_is_accept(false)
    {
        //
    }

    ServerCacheSingle(QObject* sender, QString functionName,
                      QString url, QString id_msg, QObject *parent)
        : ServerCacheSingle(sender, functionName, url, id_msg, QJsonObject(), parent)
    {
        //
    }

    QByteArray formRequest() { return m_json->toJsonDocument().toJson(); }

    QObject* sender()      { return m_sender; }
    QString functionName() { return m_functionName; }
    QString id_msg()       { return m_id_msg; }
    WJsonTemplate* json()  { return m_json; }
    WEnum::Request_priority priority() { return m_priority; }
    int secAfterRequest() { return m_json->dateTime().secsTo(QDateTime::currentDateTime()); }
    bool isAccept() { return m_is_accept; }
    void accept()   { m_is_accept = true; }

private:
    QObject* m_sender;
    QString m_functionName;
    QString m_id_msg;
    WJsonTemplate* m_json;
    WEnum::Request_priority m_priority;
    bool m_is_accept;
};

#endif // SERVER_CACHE_SINGLE_H
