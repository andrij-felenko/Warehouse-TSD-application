#include "url.h"
#include <QDebug>

Url _url;

Url::Url(QObject *parent) : QObject(parent)
{
    // first word to request -----------------------------------------------------------------------
    m_list.push_back({ Get,       "get",       Enum::Version_0_1 });
    m_list.push_back({ Set,       "set",       Enum::Version_0_1 });
    m_list.push_back({ Accept,    "accept",    Enum::Version_0_1 });
    m_list.push_back({ Remove,    "remove",    Enum::Version_0_1 });
    m_list.push_back({ Update,    "update",    Enum::Version_0_1 });
    m_list.push_back({ Reserve,   "reserve",   Enum::Version_0_1 });
    m_list.push_back({ Unreserve, "unreserve", Enum::Version_0_1 });

    // type of document ----------------------------------------------------------------------------
    m_list.push_back({ Allotted,  "Allocated", Enum::Version_0_1 });
    m_list.push_back({ Delivery,  "Delivery",  Enum::Version_0_1 });
    m_list.push_back({ Inventory, "Inventory", Enum::Version_0_1 });
    m_list.push_back({ Picking,   "Picking",   Enum::Version_0_1 });
    m_list.push_back({ Purchase,  "Purchase",  Enum::Version_0_1 });
    m_list.push_back({ Receiving, "Receiving", Enum::Version_0_1 });

    // optional words ------------------------------------------------------------------------------
    m_list.push_back({ All,  "All",  Enum::Version_0_1 });
    m_list.push_back({ By,   "By",   Enum::Version_0_1 });
    m_list.push_back({ Line, "Line", Enum::Version_0_1 });
    m_list.push_back({ List, "List", Enum::Version_0_1 });
    m_list.push_back({ New,  "New",  Enum::Version_0_1 });

    // other ---------------------------------------------------------------------------------------
    m_list.push_back({ Cell,        "Cell",        Enum::Version_0_1 });
    m_list.push_back({ Consignment, "Consignment", Enum::Version_0_1 });
    m_list.push_back({ Container,   "Container",   Enum::Version_0_1 });
    m_list.push_back({ Department,  "Department",  Enum::Version_0_1 });
    m_list.push_back({ Document,    "Document",    Enum::Version_0_1 });
    m_list.push_back({ Employee,    "Employee",    Enum::Version_0_1 });
    m_list.push_back({ Error,   "Error",   Enum::Version_0_1 });
    m_list.push_back({ Icon,    "Icon",    Enum::Version_0_1 });
    m_list.push_back({ Id,      "Id",      Enum::Version_0_1 });
    m_list.push_back({ Image,   "Image",   Enum::Version_0_1 });
    m_list.push_back({ Info,    "Info",    Enum::Version_0_1 });
    m_list.push_back({ Transit, "Transit", Enum::Version_0_1 });
}

Url::Url_enum Url::fromString(QString name, Enum::Version version_)
{
    return _url.p_fromString(name, version_);
}

QString Url::toString(Url::Url_enum key, Enum::Version version_)
{
    return _url.p_toString(key, version_);
}

Url::Url_enum Url::p_fromString(QString name, Enum::Version version_)
{
    Url_enum key;
    Enum::Version lastSuitableVersion(Enum::Version_none);
    for (auto it : m_list)
        if (it.name == name)
            if (+version_ >= +it.version)
                if (+it.version > +lastSuitableVersion){
                    key = it.key;
                    lastSuitableVersion = it.version;
                    if (version_ == lastSuitableVersion)
                        return key;
                }
    if (lastSuitableVersion != Enum::Version_none)
        return key;
    return errorKey();
}

QString Url::p_toString(Url::Url_enum key, Enum::Version version_)
{
    if (errorKey() == key)
        return Static::undefined();

    QString value("");
    Enum::Version lastSuitableVersion(Enum::Version_none);
    for (auto it : m_list)
        if (it.key == key)
            if (+version_ >= +it.version)
                if (+it.version > +lastSuitableVersion){
                    value = it.name;
                    lastSuitableVersion = it.version;
                    if (version_ == lastSuitableVersion)
                        return value;
                }
    if (lastSuitableVersion != Enum::Version_none)
        return value;
    return Static::undefined();
}

QString Url::compareUrl(std::initializer_list <Url_enum> list, Enum::Version version_)
{
    QString ret("");
    for (auto it : list)
        ret += toString(it, version_);
    return ret;
}

QList<Url::Url_enum> Url::disunite(const QString& url, Enum::Version version_)
{
    QList<Url::Url_enum> list;
    QString value("");
    for (int i = 0; i < url.length(); i++){
        if (url[i].isUpper() and not value.isEmpty()){
            auto key = fromString(value, version_);
            if (key != errorKey())
                list.push_back(key);
            value.clear();
            value += url[i];
        }
        else
            value += url[i];
    }
    return list;
}
