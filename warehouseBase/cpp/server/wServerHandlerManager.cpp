#include "wServerHandlerManager.h"
#include "wSingleton.h"

WServerHandlerManager::WServerHandlerManager(QObject *parent) : QObject(parent)
{
    m_baseHandler = new WServerHandler(this);
}

bool WServerHandlerManager::isUrlContains(QList<WUrl::WUrl_enum> url)
{
    if (m_baseHandler->isContains(url))
        return true;
    for (auto it : m_list)
        if (it->isContains(url))
            return true;
    return false;
}

bool WServerHandlerManager::isUrlContains(QString url)
{
    return isUrlContains(WUrl::disunite(url));
}

bool WServerHandlerManager::registrate(WHandlerTemplate* handler)
{
    for (auto it : handler->getList()){
        if (m_baseHandler->isContains(it))
            WMessage::get().setWarningMessage(WUrl::compareUrl(it) + QObject::tr(" не будет обработан."),
                                              WEnum::Priority_low);
        for (auto subIt : m_list)
            if (subIt->isContains(it))
                WMessage::get().setWarningMessage(WUrl::compareUrl(it) + QObject::tr(" не будет обработан."),
                                                 WEnum::Priority_low);
    }
    m_list.push_back(handler);
    return true;
}

/*! \brief Принимает запросы от сервера и направляет их в нужный обработчик */
void WServerHandlerManager::sendRequest(QList <WUrl::WUrl_enum> url, WJsonTemplate* json)
{
    qDebug() << url << WUrl::compareUrl(url);
    if (m_baseHandler->isContains(url)){
        m_baseHandler->handler(url, json);
        return;
    }

    for (auto it : m_list)
        if (it->isContains(url)){
            it->handler(url, json);
            return;
        }

    WMessage::get().setWarningMessage(WUrl::compareUrl(url) + QObject::tr(" не найдено решение в списке методов"),
                                      WEnum::Priority_middle);
}
