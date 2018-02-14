#include "cellSingle.h"

CellSingle::CellSingle(QObject *parent) : CacheSingle(parent)
{
    //
}

CellSingle::CellSingle(const QJsonObject &obj, QObject *parent) : CellSingle(parent)
{
    fromJson(obj);
}

QJsonObject CellSingle::toJson() const
{
    QJsonObject obj = CacheSingle::toJson();
    WJson::insert(obj, WJson::Warehouse_id, QJsonValue(m_warehouseId));
    return obj;
}

void CellSingle::fromJson(const QJsonObject& obj)
{
    CellSingle::fromJson(obj);

    if (WJson::contains(obj, WJson::Warehouse_id))
        setWarehouseId(WJson::get(obj, WJson::Warehouse_id).toString());
}

void CellSingle::setWarehouseId(QString warehouseId)
{
    if (m_warehouseId != warehouseId){
        m_warehouseId = warehouseId;
        emit warehouseIdChanged(m_warehouseId);
    }
}
