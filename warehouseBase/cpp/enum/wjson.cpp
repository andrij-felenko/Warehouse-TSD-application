#include "wjson.h"

WJson _wjson;

WJson::WJson(QObject* parent) : QObject(parent)
{
    // basic value -----------------------------------------------------------------------------
    m_list.push_back({ Barcode, "barcode", WEnum::Version_0_1 });
    m_list.push_back({ Id,      "id",      WEnum::Version_0_1 });
    m_list.push_back({ Guid,    "guid",    WEnum::Version_0_1 });
    m_list.push_back({ Cargo,   "cargo",   WEnum::Version_0_1 });
    m_list.push_back({ Key,     "key",     WEnum::Version_0_1 });
    m_list.push_back({ Line,    "line",    WEnum::Version_0_1 });
    m_list.push_back({ List,    "list",    WEnum::Version_0_1 });
    m_list.push_back({ Name,    "name",    WEnum::Version_0_1 });
    m_list.push_back({ Parent,  "parent",  WEnum::Version_0_1 });

    // warehouse value -------------------------------------------------------------------------
    // cell
    m_list.push_back({ Cell_id,             "cell_id",             WEnum::Version_0_1 });
    m_list.push_back({ Cell_id_list,        "cell_id_list",        WEnum::Version_0_1 });
    m_list.push_back({ Cell_name,           "cell_name",           WEnum::Version_0_1 });
    m_list.push_back({ Cell_sender_id,      "cell_sender_id",      WEnum::Version_0_1 });
    m_list.push_back({ Cell_sender_name,    "cell_sender_name",    WEnum::Version_0_1 });
    m_list.push_back({ Cell_receiver_id,    "cell_receiver_id",    WEnum::Version_0_1 });
    m_list.push_back({ Cell_receiver_name,  "cell_receiver_name",  WEnum::Version_0_1 });
    m_list.push_back({ Cell_reason_id,      "cell_reason_id",      WEnum::Version_0_1 });
    m_list.push_back({ Cell_reason_name,    "cell_reason_name",    WEnum::Version_0_1 });
    m_list.push_back({ Cell_reason_comment, "cell_reason_comment", WEnum::Version_0_1 });
    // consignment
    m_list.push_back({ Consignment,      "consignment",      WEnum::Version_0_1 });
    m_list.push_back({ Consignment_id,   "consignment_id",   WEnum::Version_0_1 });
    m_list.push_back({ Consignment_name, "consignment_name", WEnum::Version_0_1 });
    // container
    m_list.push_back({ Container_id_list,        "container_id_list",        WEnum::Version_0_1 });
    m_list.push_back({ Container_id,             "container_id",             WEnum::Version_0_1 });
    m_list.push_back({ Container_name,           "container_name",           WEnum::Version_0_1 });
    m_list.push_back({ Container_reason_id,      "container_reason_id",      WEnum::Version_0_1 });
    m_list.push_back({ Container_reason_name,    "container_reason_name",    WEnum::Version_0_1 });
    m_list.push_back({ Container_reason_comment, "container_reason_comment", WEnum::Version_0_1 });
    m_list.push_back({ Container_sender_id,      "container_sender_id",      WEnum::Version_0_1 });
    m_list.push_back({ Container_sender_name,    "container_sender_name",    WEnum::Version_0_1 });
    m_list.push_back({ Container_receiver_id,    "container_receiver_id",    WEnum::Version_0_1 });
    m_list.push_back({ Container_receiver_name,  "container_receiver_name",  WEnum::Version_0_1 });
    // dictionary
    m_list.push_back({ ModelTypeId, "model_type_id", WEnum::Version_0_1 });
    // nomenclature
    m_list.push_back({ Nomenclature_id,       "nomenclature_id",       WEnum::Version_0_1 });
    m_list.push_back({ Nomenclature_name,     "nomenclature_name",     WEnum::Version_0_1 });
    m_list.push_back({ Nomenclature_group_id, "nomenclature_group_id", WEnum::Version_0_1 });
    // nomenclature by
    m_list.push_back({ By_weight,      "by_weight",      WEnum::Version_0_1 });
    m_list.push_back({ By_piece,       "by_piece",       WEnum::Version_0_1 });
    m_list.push_back({ By_date,        "by_date",        WEnum::Version_0_1 });
    m_list.push_back({ By_consignment, "by_consignment", WEnum::Version_0_1 });
    m_list.push_back({ By_serial,      "by_serial",      WEnum::Version_0_1 });
    // quality
    m_list.push_back({ Quality_id,             "quality_id",             WEnum::Version_0_1 });
    m_list.push_back({ Quality_name,           "quality_name",           WEnum::Version_0_1 });
    m_list.push_back({ Quality_reason_id,      "quality_reason_id",      WEnum::Version_0_1 });
    m_list.push_back({ Quality_reason_name,    "quality_reason_name",    WEnum::Version_0_1 });
    m_list.push_back({ Quality_reason_comment, "quality_reason_comment", WEnum::Version_0_1 });
    // warehouse
    m_list.push_back({ Warehouse_id,            "warehouse_id",            WEnum::Version_0_1 });
    m_list.push_back({ Warehouse_name,          "warehouse_name",          WEnum::Version_0_1 });
    m_list.push_back({ Warehouse_sender_id,     "warehouse_sender_id",     WEnum::Version_0_1 });
    m_list.push_back({ Warehouse_sender_name,   "warehouse_sender_name",   WEnum::Version_0_1 });
    m_list.push_back({ Warehouse_receiver_id,   "warehouse_receiver_id",   WEnum::Version_0_1 });
    m_list.push_back({ Warehouse_receiver_name, "warehouse_receiver_name", WEnum::Version_0_1 });

    // date ------------------------------------------------------------------------------------
    m_list.push_back({ Date,            "date",            WEnum::Version_0_1 });
    m_list.push_back({ Date_time,       "date_time",       WEnum::Version_0_1 });
    m_list.push_back({ Date_block,      "date_block",      WEnum::Version_0_1 });
    m_list.push_back({ Date_packing,    "date_packing",    WEnum::Version_0_1 });
    m_list.push_back({ Date_production, "date_production", WEnum::Version_0_1 });
    m_list.push_back({ Date_created,    "date_created",    WEnum::Version_0_1 });
    m_list.push_back({ Date_accepted,   "date_accepted",   WEnum::Version_0_1 });
    m_list.push_back({ Date_completed,  "date_completed",  WEnum::Version_0_1 });
    m_list.push_back({ ShelfLife,       "shelf_life",      WEnum::Version_0_1 });

    // dimension -------------------------------------------------------------------------------
    m_list.push_back({ Height, "height", WEnum::Version_0_1 });
    m_list.push_back({ Length, "length", WEnum::Version_0_1 });
    m_list.push_back({ Weight, "weight", WEnum::Version_0_1 });
    m_list.push_back({ Width,  "width",  WEnum::Version_0_1 });

    // document --------------------------------------------------------------------------------
    m_list.push_back({ Document_id,          "document_id",             WEnum::Version_0_1 });
    m_list.push_back({ Document_date,        "document_date",           WEnum::Version_0_1 });
    m_list.push_back({ Document_name,        "document_name",           WEnum::Version_0_1 });
    m_list.push_back({ Document_header,      "document_header",         WEnum::Version_0_1 });
    m_list.push_back({ Supplier,             "supplier",                WEnum::Version_0_1 });
    m_list.push_back({ IsStaticCellContains, "is_static_cell_contains", WEnum::Version_0_1 });
    m_list.push_back({ IsCanChangeCell,      "is_can_change_cell",      WEnum::Version_0_1 });
    m_list.push_back({ IsTwoVerifyAccepted,  "is_two_verify_accepted",  WEnum::Version_0_1 });
    m_list.push_back({ IsGeoposition,        "is_geoposition",          WEnum::Version_0_1 });

    // document line ---------------------------------------------------------------------------
    m_list.push_back({ Actual,      "actual",      WEnum::Version_0_1 });
    m_list.push_back({ Line_id,     "line_id",     WEnum::Version_0_1 });
    m_list.push_back({ Line_number, "line_number", WEnum::Version_0_1 });
    m_list.push_back({ Plan,        "plan",        WEnum::Version_0_1 });
    m_list.push_back({ Status,      "status",      WEnum::Version_0_1 });
    m_list.push_back({ Transit,     "transit",     WEnum::Version_0_1 });
    // is
    m_list.push_back({ Is_done,    "is_done",    WEnum::Version_0_1 });
    m_list.push_back({ Is_default, "is_default", WEnum::Version_0_1 });
    m_list.push_back({ Is_transit, "is_transit", WEnum::Version_0_1 });
    // quantity
    m_list.push_back({ Quantity,         "quantity",         WEnum::Version_0_1 });
    m_list.push_back({ Quantity_pallet,  "quantity_pallet",  WEnum::Version_0_1 });
    m_list.push_back({ Quantity_carton,  "quantity_carton",  WEnum::Version_0_1 });
    m_list.push_back({ Quantity_packing, "quantity_packing", WEnum::Version_0_1 });

    // employee --------------------------------------------------------------------------------
    m_list.push_back({ Employee_id,            "employee_id",            WEnum::Version_0_1 });
    m_list.push_back({ Employee_name,          "employee_name",          WEnum::Version_0_1 });
    m_list.push_back({ Employee_sender_id,     "employee_sender_id",     WEnum::Version_0_1 });
    m_list.push_back({ Employee_sender_name,   "employee_sender_name",   WEnum::Version_0_1 });
    m_list.push_back({ Employee_receiver_id,   "employee_receiver_id",   WEnum::Version_0_1 });
    m_list.push_back({ Employee_receiver_name, "employee_receiver_name", WEnum::Version_0_1 });
    m_list.push_back({ Password,               "password",               WEnum::Version_0_1 });
    m_list.push_back({ Provider_id,            "provider_id",            WEnum::Version_0_1 });
    m_list.push_back({ Provider_name,          "provider_name",          WEnum::Version_0_1 });

    // server key ------------------------------------------------------------------------------
    m_list.push_back({ Code,    "code",    WEnum::Version_0_1 });
    m_list.push_back({ Data,    "data",    WEnum::Version_0_1 });
    m_list.push_back({ Error,   "error",   WEnum::Version_0_1 });
    m_list.push_back({ Meta,    "meta",    WEnum::Version_0_1 });
    m_list.push_back({ Message, "message", WEnum::Version_0_1 });
    m_list.push_back({ Request, "request", WEnum::Version_0_1 });
    m_list.push_back({ Result,  "result",  WEnum::Version_0_1 });
    m_list.push_back({ Text,    "text",    WEnum::Version_0_1 });
    m_list.push_back({ Url,     "url",     WEnum::Version_0_1 });

    // other ----------------------------------------------------------------------------------
    m_list.push_back({ Folder, "folder", WEnum::Version_0_1 });
}

QString WJson::value(WJson_enum key, QString default_, WEnum::Version version_)
{
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
    return default_;
}

QJsonObject WJson::createObject(WJson::WJson_enum key, const QJsonValue& value_insert, WEnum::Version version_)
{
    QJsonObject obj;
    WJson::insert(obj, key, value_insert, version_);
    return obj;
}

/*!
 * \brief WJson::createObject
 * \code auto t = WJson::createObject({ std::make_pair(WJson::Name, "1"),
                                        std::make_pair(WJson::Transit, "2") });
   \endcode
 * \param list
 * \param version_
 * \return
 */
QJsonObject WJson::createObject(std::initializer_list<std::pair <WJson::WJson_enum, QJsonValue>> list,
                                WEnum::Version version_)
{
    QJsonObject obj;
    for (auto it : list)
        WJson::insert(obj, it.first, it.second, version_);
    return obj;
}

QJsonValue WJson::createValue(WJson::WJson_enum key, const QJsonValue& value_insert, WEnum::Version version_)
{
    return QJsonValue(WJson::createObject(key, value_insert, version_));
}

QJsonValue WJson::createValue(std::initializer_list<std::pair <WJson::WJson_enum, QJsonValue>> list,
                              WEnum::Version version_)
{
    return QJsonValue(WJson::createObject(list, version_));
}

QString WJson::toString(WJson_enum key, WEnum::Version version_)
{
    return _wjson.value(key, WStatic::undefined(), version_);
}

QString WJson::toString(int key, int version_)
{
    return WJson::toString(static_cast <WJson_enum> (key), static_cast <WEnum::Version> (version_));
}

QJsonValue WJson::get(const QJsonObject& obj, WJson_enum key, WEnum::Version version_)
{
    return obj.value(WJson::toString(key, version_));
}

QJsonValue WJson::get(const QJsonValue& value, WJson_enum key, WEnum::Version version_)
{
    return WJson::get(value.toObject(), key, version_);
}

bool WJson::contains(const QJsonObject& obj,  WJson_enum key, WEnum::Version version_)
{
    return obj.contains(WJson::toString(key, version_));
}

bool WJson::contains(const QJsonValue& value, WJson_enum key, WEnum::Version version_)
{
    return WJson::contains(value.toObject(), key, version_);
}

bool WJson::insert(QJsonObject& obj, WJson_enum key, const QJsonValue& value_insert,
                  WEnum::Version version_)
{
    if (WStatic::undefined() != WJson::toString(key, version_)){
        obj.insert(WJson::toString(key, version_), value_insert);
        return true;
    }
    return false;
}
