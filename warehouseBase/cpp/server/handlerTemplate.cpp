#include "handlerTemplate.h"

HandlerTemplate::HandlerTemplate(QObject *parent) : QObject(parent)
{
    //
}

bool HandlerTemplate::registrateUrl(QList <WUrl::WUrl_enum> url){
    m_list.push_back(url);
}

bool HandlerTemplate::registrateUrl(std::initializer_list<WUrl::WUrl_enum> url)
{
    registrateUrl(WUrl::compareUrlList(url));
}

bool HandlerTemplate::isContains(QList<WUrl::WUrl_enum> url)
{
    for (auto it : m_list)
        if (it == url)
            return true;
    return false;
}

bool HandlerTemplate::isContains(QString url, WEnum::Version version)
{
    auto list_ = WUrl::disunite(url, version);
    for (auto it : m_list)
        if (it == list_)
            return true;
    return false;
}
