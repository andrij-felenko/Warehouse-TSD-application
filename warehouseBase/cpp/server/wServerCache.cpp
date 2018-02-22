#include "wServerCache.h"

WServerCache::WServerCache(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(5*1000);
    m_timer->start();

    QObject::connect(m_timer, &QTimer::timeout, this, &WServerCache::trySendServerCache);
}

WServerCacheSingle* WServerCache::add(WServerCacheSingle *single)
{
    cache_list.push_back(single);
    return single;
}

void WServerCache::remove(QString id)
{
    for (auto it : cache_list)
        if (it->json()->request() == id)
            cache_list.removeOne(it);
}

WServerCacheSingle* WServerCache::getOne(QString id)
{
    for (auto it : cache_list)
        if (not it->isAccept())
            if (it->json()->request() == id or it->id_msg() == id)
                return it;
    return nullptr;
}

void WServerCache::trySendServerCache()
{
    for (auto it : cache_list)
        if (it->priority() == WEnum::Request_can_cache)
            if (it->secAfterRequest() > 10)
                emit post(it->json()->url(), it->json()->toJsonDocument());
}
