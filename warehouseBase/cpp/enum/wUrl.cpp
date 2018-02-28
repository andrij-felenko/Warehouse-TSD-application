#include "wUrl.h"
#include <QDebug>

WUrl _wurl;

WUrl::WUrl(QObject *parent) : QObject(parent)
{
    // first word to request -----------------------------------------------------------------------
    m_list.push_back({ Get,       "get",       WEnum::Version_1_0 });
    m_list.push_back({ Set,       "set",       WEnum::Version_1_0 });
    m_list.push_back({ Accept,    "accept",    WEnum::Version_1_0 });
    m_list.push_back({ Remove,    "remove",    WEnum::Version_1_0 });
    m_list.push_back({ Update,    "update",    WEnum::Version_1_0 });
    m_list.push_back({ Reserve,   "reserve",   WEnum::Version_1_0 });
    m_list.push_back({ Unreserve, "unreserve", WEnum::Version_1_0 });

    // type of document ----------------------------------------------------------------------------
    m_list.push_back({ Allotted,  "Allotted",  WEnum::Version_1_0 });
    m_list.push_back({ Delivery,  "Delivery",  WEnum::Version_1_0 });
    m_list.push_back({ Inventory, "Inventory", WEnum::Version_1_0 });
    m_list.push_back({ Picking,   "Picking",   WEnum::Version_1_0 });
    m_list.push_back({ Purchase,  "Purchase",  WEnum::Version_1_0 });
    m_list.push_back({ Receiving, "Receiving", WEnum::Version_1_0 });

    // optional words ------------------------------------------------------------------------------
    m_list.push_back({ All,   "All",   WEnum::Version_1_0 });
    m_list.push_back({ By,    "By",    WEnum::Version_1_0 });
    m_list.push_back({ Cache, "Cache", WEnum::Version_1_0 });
    m_list.push_back({ Line,  "Line",  WEnum::Version_1_0 });
    m_list.push_back({ List,  "List",  WEnum::Version_1_0 });
    m_list.push_back({ New,   "New",   WEnum::Version_1_0 });

    // other ---------------------------------------------------------------------------------------
    m_list.push_back({ Barcode,      "Barcode",      WEnum::Version_1_0 });
    m_list.push_back({ Cell,         "Cell",         WEnum::Version_1_0 });
    m_list.push_back({ Consignment,  "Consignment",  WEnum::Version_1_0 });
    m_list.push_back({ Container,    "Container",    WEnum::Version_1_0 });
    m_list.push_back({ Department,   "Department",   WEnum::Version_1_0 });
    m_list.push_back({ Document,     "Document",     WEnum::Version_1_0 });
    m_list.push_back({ Employee,     "Employee",     WEnum::Version_1_0 });
    m_list.push_back({ Error,        "Error",        WEnum::Version_1_0 });
    m_list.push_back({ Icon,         "Icon",         WEnum::Version_1_0 });
    m_list.push_back({ Id,           "Id",           WEnum::Version_1_0 });
    m_list.push_back({ Image,        "Image",        WEnum::Version_1_0 });
    m_list.push_back({ Info,         "Info",         WEnum::Version_1_0 });
    m_list.push_back({ Model,        "Model",        WEnum::Version_1_0 });
    m_list.push_back({ Nomenclature, "Nomenclature", WEnum::Version_1_0 });
    m_list.push_back({ Quality,      "Quality",      WEnum::Version_1_0 });
    m_list.push_back({ Storage,      "Storage",      WEnum::Version_1_0 });
    m_list.push_back({ Transit,      "Transit",      WEnum::Version_1_0 });
    m_list.push_back({ Type,         "Type",         WEnum::Version_1_0 });
    m_list.push_back({ Unit,         "Unit",         WEnum::Version_1_0 });
}

WUrl::WUrl_enum WUrl::fromInt(int key)
{
    if (not _wurl.contains(static_cast <WUrl_enum> (key)))
        return WUrl_enum::___;
    return static_cast <WUrl_enum> (key);
}

WUrl::WUrl_enum WUrl::fromString(QString name, WEnum::Version version_)
{
    return _wurl.p_fromString(name, version_);
}

QString WUrl::toString(WUrl::WUrl_enum key, WEnum::Version version_)
{
    return _wurl.p_toString(key, version_);
}

QString WUrl::toString(int key, WEnum::Version version_)
{
    return _wurl.p_toString(static_cast <WUrl::WUrl_enum> (key), version_);
}

WUrl::WUrl_enum WUrl::p_fromString(QString name, WEnum::Version version_)
{
    WUrl_enum key;
    WEnum::Version lastSuitableVersion(WEnum::Version_none);
    for (auto it : m_list)
        if (it.name == name)
            if (+version_ >= +it.version)
                if (+it.version > +lastSuitableVersion){
                    key = it.key;
                    lastSuitableVersion = it.version;
                    if (version_ == lastSuitableVersion)
                        return key;
                }
    if (lastSuitableVersion != WEnum::Version_none)
        return key;
    return errorKey();
}

QString WUrl::p_toString(WUrl::WUrl_enum key, WEnum::Version version_)
{
    if (errorKey() == key)
        return WStatic::undefined();

    QString value("");
    WEnum::Version lastSuitableVersion(WEnum::Version_none);
    for (auto it : m_list)
        if (it.key == key)
            if (+version_ >= +it.version)
                if (+it.version > +lastSuitableVersion){
                    value = it.name;
                    lastSuitableVersion = it.version;
                    if (version_ == lastSuitableVersion)
                        return value;
                }
    if (lastSuitableVersion != WEnum::Version_none)
        return value;
    return WStatic::undefined();
}

bool WUrl::contains(WUrl::WUrl_enum key)
{
    return _wurl.m_contains(key);
}

bool WUrl::m_contains(WUrl::WUrl_enum key)
{
    for (auto it : m_list)
        if (it.key == key)
            return true;
    return false;
}

QString WUrl::compareUrl(std::initializer_list<WUrl_enum> list, WEnum::Version version_)
{
    QString ret("");
    for (auto it : list)
        ret += toString(it, version_);
    return ret;
}

QString WUrl::compareUrl(QList<int> list, WEnum::Version version_)
{
    QString ret("");
    for (auto it : list)
        ret += toString(static_cast <WUrl::WUrl_enum> (it), version_);
    return ret;
}

QString WUrl::compareUrl(QList<WUrl_enum> list, WEnum::Version version_)
{
    QString ret("");
    for (auto it : list)
        ret += toString(it, version_);
    return ret;
}

QList<WUrl::WUrl_enum> WUrl::compareUrlList(std::initializer_list<WUrl::WUrl_enum> list)
{
    QList <WUrl::WUrl_enum> url;
    for (auto it : list)
        url.push_back(it);
    return url;
}

QList<WUrl::WUrl_enum> WUrl::disunite(const QString& url, WEnum::Version version_)
{
    QList<WUrl::WUrl_enum> list;
    QString value("");
    for (int i = 0; i < url.length(); i++){
        if (url[i].isUpper() and not value.isEmpty()){
            auto key = fromString(value, version_);
            if (key != errorKey())
                list.push_back(key);
            value.clear();
            value += url[i];
        }
        else if (i + 1 == url.length()){
            value += url[i];
            auto key = fromString(value, version_);
            if (key != errorKey())
                list.push_back(key);
        }
        else
            value += url[i];
    }
    return list;
}

bool WUrl::isEqual(QList<WUrl::WUrl_enum> url, std::initializer_list<WUrl::WUrl_enum> list)
{
    return url == compareUrlList(list);
}

int WUrl::versionToInt()
{
    return static_cast <int> (_wurl.version());
}
