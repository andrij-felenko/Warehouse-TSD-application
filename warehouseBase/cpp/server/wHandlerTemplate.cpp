#include "wHandlerTemplate.h"
#include "wSingleton.h"

WHandlerTemplate::WHandlerTemplate(QObject *parent) : QObject(parent)
{
    //
}

bool WHandlerTemplate::registrateUrl(QList <WUrl::WUrl_enum> url, WEnum::Request_priority priority){
    for (auto it : url)
        if (not WUrl::contains(it)){
            WMessage::get().setWarningMessage(QObject::tr("failed to registrate url: ").append(WUrl::compareUrl(url)),
                                              WEnum::Priority_middle_bellow);
            return false;
        }

    for (auto it : m_list)
        if (it.first == url){
            WMessage::get().setWarningMessage(QObject::tr("duplicates url: ").append(WUrl::compareUrl(url)),
                                              WEnum::Priority_middle_bellow);
            return false;
        }

    m_list.push_back(std::make_pair(url, priority));
    return true;
}

bool WHandlerTemplate::registrateUrl(std::initializer_list<WUrl::WUrl_enum> url, WEnum::Request_priority priority)
{
    return registrateUrl(QList <WUrl::WUrl_enum> (url), priority);
}

bool WHandlerTemplate::isContains(QList<WUrl::WUrl_enum> url) const
{
    for (auto it : m_list)
        if (it.first == url)
            return true;
    return false;
}

bool WHandlerTemplate::isContains(QString url, WEnum::Version version) const
{
    auto list_ = WUrl::disunite(url, version);
    for (auto it : m_list)
        if (it.first == list_)
            return true;
    return false;
}

QList<QList<WUrl::WUrl_enum>> WHandlerTemplate::getList() const
{
    QList<QList<WUrl::WUrl_enum>> list;
    for (auto it : m_list)
        list.push_back(it.first);
    return list;
}
