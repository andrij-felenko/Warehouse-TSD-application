#ifndef SERVER_CACHE_H
#define SERVER_CACHE_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include "serverCacheSingle.h"

class ServerCache : public QObject
{
    Q_OBJECT
public:
    explicit ServerCache(QObject *parent = nullptr);

    ServerCacheSingle* add(ServerCacheSingle* single);
    void remove(QString id);
    ServerCacheSingle* getOne(QString id);

signals:
    void get(QString url);
    void post(QString url, QJsonDocument document);

private:
    QList <ServerCacheSingle*> cache_list;
    QTimer *m_timer; ///< Краткое описание timer
    void trySendServerCache();
};

#endif // SERVER_CACHE_H
