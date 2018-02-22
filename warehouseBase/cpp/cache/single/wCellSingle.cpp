#include "wCellSingle.h"

WCellSingle::WCellSingle(QObject *parent) : WCacheSingle(parent)
{
    //
}

WCellSingle::WCellSingle(const QJsonObject &obj, QObject *parent) : WCellSingle(parent)
{
    fromJson(obj);
}

QJsonObject WCellSingle::toJson() const
{
    QJsonObject obj = WCacheSingle::toJson();
    WJson::insert(obj, WJson::Warehouse_id, QJsonValue(m_warehouseId));
    return obj;
}

void WCellSingle::fromJson(const QJsonObject& obj)
{
    WCellSingle::fromJson(obj);

    if (WJson::contains(obj, WJson::Warehouse_id))
        setWarehouseId(WJson::get(obj, WJson::Warehouse_id).toString());
}

void WCellSingle::setWarehouseId(QString warehouseId)
{
    if (m_warehouseId != warehouseId){
        m_warehouseId = warehouseId;
        emit warehouseIdChanged(m_warehouseId);
    }
}

QDataStream& operator << (QDataStream& s, WCellSingle& d)
{
    return s << static_cast <WCacheSingle&> (d) << d.m_warehouseId;
}

QDataStream& operator >> (QDataStream& s, WCellSingle& d)
{
    return s >> static_cast <WCacheSingle&> (d) >> d.m_warehouseId;
}
