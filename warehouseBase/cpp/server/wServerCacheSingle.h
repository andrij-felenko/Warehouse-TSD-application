#ifndef WSERVER_CACHE_SINGLE_H
#define WSERVER_CACHE_SINGLE_H

#include <QtCore/QObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QDateTime>
#include "enum/wEnum.h"
#include "wJsonTemplate.h"

class WServerCacheSingle : public QObject
{
public:
    WServerCacheSingle(QObject* sender = nullptr, QString functionName = "",
                       QString url = "", QString id_msg = "",
                       QJsonValue json = QJsonValue(), QObject *parent = nullptr,
                       WEnum::Request_priority priority = WEnum::Request_can_ignore);

    WServerCacheSingle(QObject* sender, QString functionName,
                       QString url, QString id_msg, QObject *parent);

    ~WServerCacheSingle();

    QByteArray formRequest() const;
    QObject* sender()      const;
    QString functionName() const;
    QString id_msg()       const;
    WJsonTemplate* json()  const;
    WEnum::Request_priority priority() const;
    WEnum::ServerCacheStatus status() const;
    int secAfterRequest() const;
    void setStatus(WEnum::ServerCacheStatus status);

private:
    QObject* m_sender;
    QString m_functionName;
    QString m_id_msg;
    WJsonTemplate* m_json;
    WEnum::Request_priority m_priority;
    WEnum::ServerCacheStatus m_status;
};

#endif // SERVER_CACHE_SINGLE_H
