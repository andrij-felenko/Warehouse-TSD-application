#include "serverHandlerManager.h"
#include "singleton.h"

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
    for (auto it : handler->getList()){
        if (m_baseHandler->isContains(it))
            Message::get().setWarningMessage(WUrl::compareUrl(it) + QObject::tr(" не будет обработан."),
                                             WEnum::Priority_low);
        for (auto subIt : m_list)
            if (subIt->isContains(it))
                Message::get().setWarningMessage(WUrl::compareUrl(it) + QObject::tr(" не будет обработан."),
                                                 WEnum::Priority_low);
    }
    m_list.push_back(handler);
    return true;
}

void ServerHandlerManager::sendRequest(QList <WUrl::WUrl_enum> url, WJsonTemplate* json)
{
    Q_UNUSED(url)
    Q_UNUSED(json)
    // FIXME я не помню зачем эта функция, забыл и все
}
