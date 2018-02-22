#ifndef SERVER_CACHE_H
#define SERVER_CACHE_H

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include "wServerCacheSingle.h"

class WServerCache : public QObject
{
    Q_OBJECT
public:
    explicit WServerCache(QObject *parent = nullptr);

    WServerCacheSingle* add(WServerCacheSingle* single);
    void remove(QString id);
    WServerCacheSingle* getOne(QString id);

signals:
    void get(QString url);
    void post(QString url, QJsonDocument document);

private:
    QList <WServerCacheSingle*> cache_list;
    QTimer *m_timer; ///< Краткое описание timer
    void trySendServerCache();
};

#endif // SERVER_CACHE_H
