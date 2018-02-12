#include "cellSingle.h"

CellSingle::CellSingle(QObject *parent) : QObject(parent)
{
    //
}

CellSingle::CellSingle(const QJsonObject &obj, QObject *parent) : CellSingle(parent)
{
    fromJson(obj);
}

QJsonObject CellSingle::toJson() const
{
    QJsonObject obj = CellSingle::toJson();
    WJson::insert(obj, WJson::Warehouse_id, QJsonValue(m_warehouseId));
    return obj;
}

void CellSingle::fromJson(const QJsonObject& obj)
{
    CellSingle::fromJson(obj);

    if (WJson::contains(obj, WJson::Warehouse_id))
        setWarehouseId(WJson::get(obj, WJson::Warehouse_id).toString());
}

QString CellSingle::warehouseId() const
{
    return m_warehouseId;
}

void CellSingle::resetWarehouseId()
{
    setWarehouseId(WStatic::guidDefault());
}

void CellSingle::setWarehouseId(QString warehouseId)
{
    if (m_warehouseId != warehouseId){
        m_warehouseId = warehouseId;
        emit warehouseIdChanged(m_warehouseId);
    }
}
