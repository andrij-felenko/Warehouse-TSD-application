#ifndef WCELLSINGLE_H
#define WCELLSINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wJson.h"
#include "enum/wStatic.h"
#include "wCacheSingle.h"

class WCellSingle : public WCacheSingle
{
    Q_OBJECT
    Q_PROPERTY(QString warehouseId READ       warehouseId WRITE setWarehouseId
                                   RESET resetWarehouseId NOTIFY   warehouseIdChanged)

public:
    explicit WCellSingle(QObject *parent = nullptr);
    WCellSingle(const QJsonObject &obj, QObject* parent = nullptr);
    operator WCacheSingle* () { return reinterpret_cast <WCacheSingle*> (this); }

    // Json ------------------------------------------------------------------------------------------------------------
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

    // READ ------------------------------------------------------------------------------------------------------------
    QString warehouseId() const { return m_warehouseId; }

    // RESET -----------------------------------------------------------------------------------------------------------
    void resetWarehouseId() { setWarehouseId(WStatic::guidDefault()); }

signals:
    void warehouseIdChanged(QString warehouseId);

public slots:
    void setWarehouseId(QString warehouseId);

protected:
    friend QDataStream& operator << (QDataStream &s, WCellSingle& d);
    friend QDataStream& operator >> (QDataStream &s, WCellSingle& d);

private:
    QString m_warehouseId;
};

#endif // CELLSINGLE_H
