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

/*! \brief Принимает запросы от сервера и направляет их в нужный обработчик */
void ServerHandlerManager::sendRequest(QList <WUrl::WUrl_enum> url, WJsonTemplate* json)
{
    qDebug() << json;
    qDebug() << url << WUrl::compareUrl(url);
    if (m_baseHandler->isContains(url)){
        m_baseHandler->handler(url, json);
        qDebug() << json;
        return;
    }

    for (auto it : m_list)
        if (it->isContains(url)){
            it->handler(url, json);
            qDebug() << json;
            return;
        }

    Message::get().setWarningMessage(WUrl::compareUrl(url) + QObject::tr(" не найдено решение в списке методов"),
                                     WEnum::Priority_middle);
}
