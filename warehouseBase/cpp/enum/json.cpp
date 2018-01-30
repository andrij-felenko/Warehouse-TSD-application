#include "json.h"

Json _json;

Json::Json(QObject* parent) : QObject(parent)
{
    // basic value -----------------------------------------------------------------------------
    m_list.push_back({ Barcode, "barcode", Enum::Version_0_1 });
    m_list.push_back({ Id,      "id",      Enum::Version_0_1 });
    m_list.push_back({ Guid,    "guid",    Enum::Version_0_1 });
    m_list.push_back({ Cargo,   "cargo",   Enum::Version_0_1 });
    m_list.push_back({ Key,     "key",     Enum::Version_0_1 });
    m_list.push_back({ Line,    "line",    Enum::Version_0_1 });
    m_list.push_back({ List,    "list",    Enum::Version_0_1 });
    m_list.push_back({ Name,    "name",    Enum::Version_0_1 });
    m_list.push_back({ Parent,  "parent",  Enum::Version_0_1 });

    // warehouse value -------------------------------------------------------------------------
    // cell
    m_list.push_back({ Cell_id,             "cell_id",             Enum::Version_0_1 });
    m_list.push_back({ Cell_name,           "cell_name",           Enum::Version_0_1 });
    m_list.push_back({ Cell_sender_id,      "cell_sender_id",      Enum::Version_0_1 });
    m_list.push_back({ Cell_sender_name,    "cell_sender_name",    Enum::Version_0_1 });
    m_list.push_back({ Cell_receiver_id,    "cell_receiver_id",    Enum::Version_0_1 });
    m_list.push_back({ Cell_receiver_name,  "cell_receiver_name",  Enum::Version_0_1 });
    m_list.push_back({ Cell_reason_id,      "cell_reason_id",      Enum::Version_0_1 });
    m_list.push_back({ Cell_reason_name,    "cell_reason_name",    Enum::Version_0_1 });
    m_list.push_back({ Cell_reason_comment, "cell_reason_comment", Enum::Version_0_1 });
    // consignment
    m_list.push_back({ Consignment_id,   "consignment_id",   Enum::Version_0_1 });
    m_list.push_back({ Consignment_name, "consignment_name", Enum::Version_0_1 });
    // container
    m_list.push_back({ Container_id_list,        "container_id_list",        Enum::Version_0_1 });
    m_list.push_back({ Container_id,             "container_id",             Enum::Version_0_1 });
    m_list.push_back({ Container_name,           "container_name",           Enum::Version_0_1 });
    m_list.push_back({ Container_reason_id,      "container_reason_id",      Enum::Version_0_1 });
    m_list.push_back({ Container_reason_name,    "container_reason_name",    Enum::Version_0_1 });
    m_list.push_back({ Container_reason_comment, "container_reason_comment", Enum::Version_0_1 });
    // nomenclature
    m_list.push_back({ Nomenclature_id,       "nomenclature_id",       Enum::Version_0_1 });
    m_list.push_back({ Nomenclature_name,     "nomenclature_name",     Enum::Version_0_1 });
    m_list.push_back({ Nomenclature_group_id, "nomenclature_group_id", Enum::Version_0_1 });
    // nomenclature by
    m_list.push_back({ By_weight,      "by_weight",      Enum::Version_0_1 });
    m_list.push_back({ By_piece,       "by_piece",       Enum::Version_0_1 });
    m_list.push_back({ By_date,        "by_date",        Enum::Version_0_1 });
    m_list.push_back({ By_consignment, "by_consignment", Enum::Version_0_1 });
    m_list.push_back({ By_serial,      "by_serial",      Enum::Version_0_1 });
    // quality
    m_list.push_back({ Quality_id,             "quality_id",             Enum::Version_0_1 });
    m_list.push_back({ Quality_name,           "quality_name",           Enum::Version_0_1 });
    m_list.push_back({ Quality_reason_id,      "quality_reason_id",      Enum::Version_0_1 });
    m_list.push_back({ Quality_reason_name,    "quality_reason_name",    Enum::Version_0_1 });
    m_list.push_back({ Quality_reason_comment, "quality_reason_comment", Enum::Version_0_1 });
    // warehouse
    m_list.push_back({ Warehouse_id,            "warehouse_id",            Enum::Version_0_1 });
    m_list.push_back({ Warehouse_name,          "warehouse_name",          Enum::Version_0_1 });
    m_list.push_back({ Warehouse_sender_id,     "warehouse_sender_id",     Enum::Version_0_1 });
    m_list.push_back({ Warehouse_sender_name,   "warehouse_sender_name",   Enum::Version_0_1 });
    m_list.push_back({ Warehouse_receiver_id,   "warehouse_receiver_id",   Enum::Version_0_1 });
    m_list.push_back({ Warehouse_receiver_name, "warehouse_receiver_name", Enum::Version_0_1 });

    // date ------------------------------------------------------------------------------------
    m_list.push_back({ Date,            "date",            Enum::Version_0_1 });
    m_list.push_back({ Date_time,       "date_time",       Enum::Version_0_1 });
    m_list.push_back({ Date_block,      "date_block",      Enum::Version_0_1 });
    m_list.push_back({ Date_packing,    "date_packing",    Enum::Version_0_1 });
    m_list.push_back({ Date_production, "date_production", Enum::Version_0_1 });

    // dimension -------------------------------------------------------------------------------
    m_list.push_back({ Height, "height", Enum::Version_0_1 });
    m_list.push_back({ Length, "length", Enum::Version_0_1 });
    m_list.push_back({ Weight, "weight", Enum::Version_0_1 });
    m_list.push_back({ Width,  "width",  Enum::Version_0_1 });

    // document --------------------------------------------------------------------------------
    m_list.push_back({ Document_id,     "document_id",     Enum::Version_0_1 });
    m_list.push_back({ Document_date,   "document_date",   Enum::Version_0_1 });
    m_list.push_back({ Document_name,   "document_name",   Enum::Version_0_1 });
    m_list.push_back({ Document_header, "document_header", Enum::Version_0_1 });

    // document line ---------------------------------------------------------------------------
    m_list.push_back({ Actual,      "actual",      Enum::Version_0_1 });
    m_list.push_back({ Line_id,     "line_id",     Enum::Version_0_1 });
    m_list.push_back({ Line_number, "line_number", Enum::Version_0_1 });
    m_list.push_back({ Plan,        "plan",        Enum::Version_0_1 });
    m_list.push_back({ Status,      "status",      Enum::Version_0_1 });
    m_list.push_back({ Transit,     "transit",     Enum::Version_0_1 });
    // is
    m_list.push_back({ Is_done,    "is_done",    Enum::Version_0_1 });
    m_list.push_back({ Is_default, "is_default", Enum::Version_0_1 });
    m_list.push_back({ Is_transit, "is_transit", Enum::Version_0_1 });
    // quantity
    m_list.push_back({ Quantity,         "quantity",         Enum::Version_0_1 });
    m_list.push_back({ Quantity_pallet,  "quantity_pallet",  Enum::Version_0_1 });
    m_list.push_back({ Quantity_carton,  "quantity_carton",  Enum::Version_0_1 });
    m_list.push_back({ Quantity_packing, "quantity_packing", Enum::Version_0_1 });

    // employee --------------------------------------------------------------------------------
    m_list.push_back({ Employee_id,   "employee_id",   Enum::Version_0_1 });
    m_list.push_back({ Employee_name, "employee_name", Enum::Version_0_1 });
    m_list.push_back({ Password,      "password",      Enum::Version_0_1 });
    m_list.push_back({ Provider_id,   "provider_id",   Enum::Version_0_1 });
    m_list.push_back({ Provider_name, "provider_name", Enum::Version_0_1 });

    // server key ------------------------------------------------------------------------------
    m_list.push_back({ Code,    "code",    Enum::Version_0_1 });
    m_list.push_back({ Data,    "data",    Enum::Version_0_1 });
    m_list.push_back({ Error,   "error",   Enum::Version_0_1 });
    m_list.push_back({ Meta,    "meta",    Enum::Version_0_1 });
    m_list.push_back({ Message, "message", Enum::Version_0_1 });
    m_list.push_back({ Request, "request", Enum::Version_0_1 });
    m_list.push_back({ Result,  "result",  Enum::Version_0_1 });
}

QString Json::value(Json_enum key, QString default_, Enum::Version version_)
{
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
    return default_;
}

QString Json::toString(Json_enum key, Enum::Version version_)
{
    return _json.value(key, Static::undefined(), version_);
}

QString Json::toString(int key, int version_)
{
    return Json::toString(static_cast <Json_enum> (key), static_cast <Enum::Version> (version_));
}

QJsonValue Json::get(const QJsonObject& obj, Json_enum key, Enum::Version version_)
{
    return obj.value(Json::toString(key, version_));
}

QJsonValue Json::get(const QJsonValue& value, Json_enum key, Enum::Version version_)
{
    return Json::get(value.toObject(), key, version_);
}

bool Json::contains(const QJsonObject& obj,  Json_enum key, Enum::Version version_)
{
    return obj.contains(Json::toString(key, version_));
}

bool Json::contains(const QJsonValue& value, Json_enum key, Enum::Version version_)
{
    return Json::contains(value.toObject(), key, version_);
}

bool Json::insert(QJsonObject& obj, Json_enum key, const QJsonValue& value_insert,
                  Enum::Version version_)
{
    if (Static::undefined() != Json::toString(key, version_)){
        obj.insert(Json::toString(key, version_), value_insert);
        return true;
    }
    return false;
}
