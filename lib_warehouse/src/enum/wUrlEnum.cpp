#include "enum/wUrlEnum.h"
#include <QDebug>

WUrlEnum::WUrlEnum(QObject *parent) : QObject(parent)
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
    m_list.push_back({ Supplier,     "Supplier",     WEnum::Version_1_0 });
    m_list.push_back({ Transit,      "Transit",      WEnum::Version_1_0 });
    m_list.push_back({ Type,         "Type",         WEnum::Version_1_0 });
    m_list.push_back({ Unit,         "Unit",         WEnum::Version_1_0 });
    m_list.push_back({ Warehouse,    "Warehouse",    WEnum::Version_1_0 });
}

WUrlEnum::WUrl_enum WUrlEnum::p_fromString(QString name, WEnum::Version version_)
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
    return p_errorKey();
}

QString WUrlEnum::p_toString(WUrl_enum key, WEnum::Version version_)
{
    if (p_errorKey() == key)
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

bool WUrlEnum::p_contains(WUrl_enum key)
{
    for (auto it : m_list)
        if (it.key == key)
            return true;
    return false;
}

WUrlEnum::WUrl_enum WUrlEnum::p_errorKey() { return WUrlEnum::WUrl_enum::___;         }
