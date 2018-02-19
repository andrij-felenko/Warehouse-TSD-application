#include "handlerTemplate.h"

HandlerTemplate::HandlerTemplate(QObject *parent) : QObject(parent)
{
    //
}

bool HandlerTemplate::registrateUrl(QList <WUrl::WUrl_enum> url){
    // FIXME
    m_list.push_back(url);
    return true;
}

bool HandlerTemplate::registrateUrl(std::initializer_list<WUrl::WUrl_enum> url)
{
    // FIXME
    registrateUrl(WUrl::compareUrlList(url));
    return true;
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

QList<QList<WUrl::WUrl_enum> > HandlerTemplate::getList() const
{
    return m_list;
}
