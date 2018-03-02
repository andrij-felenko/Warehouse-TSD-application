#include "wHandlerTemplate.h"
#include "wSingleton.h"

WHandlerTemplate::WHandlerTemplate(QObject *parent) : QObject(parent)
{
    //
}

bool WHandlerTemplate::registrateUrl(QList <WUrlEnum::WUrl_enum> url, WEnum::Request_priority priority){
    for (auto it : url)
        if (not WUrlConverter::contains(it)){
            WMessage::get().setWarningMessage(QObject::tr("failed to registrate url: ")
                                              .append(WUrlConverter::compareUrl(url)),
                                              WEnum::Priority_middle_bellow);
            return false;
        }

    for (auto it : m_list)
        if (it.first == url){
            WMessage::get().setWarningMessage(QObject::tr("duplicates url: ").append(WUrlConverter::compareUrl(url)),
                                              WEnum::Priority_middle_bellow);
            return false;
        }

    m_list.push_back(std::make_pair(url, priority));
    return true;
}

bool WHandlerTemplate::registrateUrl(std::initializer_list<WUrlEnum::WUrl_enum> url, WEnum::Request_priority priority)
{
    return registrateUrl(QList <WUrlEnum::WUrl_enum> (url), priority);
}

bool WHandlerTemplate::isContains(QList<WUrlEnum::WUrl_enum> url) const
{
    for (auto it : m_list)
        if (it.first == url)
            return true;
    return false;
}

bool WHandlerTemplate::isContains(QString url, WEnum::Version version) const
{
    auto list_ = WUrlConverter::disunite(url, version);
    for (auto it : m_list)
        if (it.first == list_)
            return true;
    return false;
}

QList<QList<WUrlEnum::WUrl_enum>> WHandlerTemplate::getList() const
{
    QList<QList<WUrlEnum::WUrl_enum>> list;
    for (auto it : m_list)
        list.push_back(it.first);
    return list;
}
