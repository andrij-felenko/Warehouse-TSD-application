#include "wCellSingle.h"
#include "wclass/wJsonConverter.h"

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
    WJsonConverter::insert(obj, WJsonEnum::Warehouse_id, QJsonValue(m_warehouseId));
    return obj;
}

void WCellSingle::fromJson(const QJsonObject& obj)
{
    WCellSingle::fromJson(obj);

    if (WJsonConverter::contains(obj, WJsonEnum::Warehouse_id))
        setWarehouseId(WJsonConverter::get(obj, WJsonEnum::Warehouse_id).toString());
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
