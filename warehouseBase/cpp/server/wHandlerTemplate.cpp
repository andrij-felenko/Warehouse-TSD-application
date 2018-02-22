#include "wHandlerTemplate.h"

WHandlerTemplate::WHandlerTemplate(QObject *parent) : QObject(parent)
{
    //
}

bool WHandlerTemplate::registrateUrl(QList <WUrl::WUrl_enum> url){
    // FIXME
    m_list.push_back(url);
    return true;
}

bool WHandlerTemplate::registrateUrl(std::initializer_list<WUrl::WUrl_enum> url)
{
    // FIXME
    registrateUrl(WUrl::compareUrlList(url));
    return true;
}

bool WHandlerTemplate::isContains(QList<WUrl::WUrl_enum> url)
{
    for (auto it : m_list)
        if (it == url)
            return true;
    return false;
}

bool WHandlerTemplate::isContains(QString url, WEnum::Version version)
{
    auto list_ = WUrl::disunite(url, version);
    for (auto it : m_list)
        if (it == list_)
            return true;
    return false;
}

QList<QList<WUrl::WUrl_enum>> WHandlerTemplate::getList() const
{
    return m_list;
}
