#include "serverCache.h"

ServerCache::ServerCache(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(5*1000);
    m_timer->start();

    QObject::connect(m_timer, &QTimer::timeout, this, &ServerCache::trySendServerCache);
}

void ServerCache::add(ServerCacheSingle *single)
{
    cache_list.push_back(single);
}

void ServerCache::remove(QString id)
{
    for (auto it : cache_list)
        if (it->id_request() == id or
                (it->url() == id and it->priority() != Enum::Request_priority_can_cache))
            cache_list.removeOne(it);
}

ServerCacheSingle* ServerCache::getOne(QString id)
{
    for (auto it : cache_list)
        if (not it->isAccept())
            if (it->id_request() == id or it->url() == id or it->id_msg() == id)
                return it;
    return new ServerCacheSingle();
}

void ServerCache::trySendServerCache()
{
    for (auto it : cache_list)
        if (it->priority() == Enum::Request_priority_can_cache)
            if (it->secAfterRequest() > 10){
                if (it->document().isEmpty())
                    emit get(it->url());
                else
                    emit post(it->url(), it->document());
            }
}
