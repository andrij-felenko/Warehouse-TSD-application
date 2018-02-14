#include "serverHandlerManager.h"

ServerHandlerManager::ServerHandlerManager(QObject *parent) : QObject(parent)
{
    m_baseHandler = new ServerHandler(this);
}

bool ServerHandlerManager::isUrlContains(QList<WUrl::WUrl_enum> url)
{
    if (m_baseHandler->isContains(url))
        return true;
    for (auto it : m_list)
        if (it->isContains(url))
            return true;
    return false;
}

bool ServerHandlerManager::isUrlContains(QString url)
{
    return isUrlContains(WUrl::disunite(url));
}

bool ServerHandlerManager::registrate(HandlerTemplate* handler)
{
    m_list.push_back(handler);
    // FIXME добавить проверку на совпадения ключей
}

void ServerHandlerManager::sendRequest(QList <WUrl::WUrl_enum> url, WJsonTemplate* json)
{
    //
}
