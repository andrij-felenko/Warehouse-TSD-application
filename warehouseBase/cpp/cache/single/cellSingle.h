#ifndef CELLSINGLE_H
#define CELLSINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wjson.h"
#include "enum/wstatic.h"
#include "cacheSingle.h"

class CellSingle : public CacheSingle
{
    Q_OBJECT
    Q_PROPERTY(QString warehouseId READ       warehouseId WRITE setWarehouseId
                                   RESET resetWarehouseId NOTIFY   warehouseIdChanged)

public:
    explicit CellSingle(QObject *parent = nullptr);
    CellSingle(const QJsonObject &obj, QObject* parent = nullptr);

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

private:
    QString m_warehouseId;
};

#endif // CELLSINGLE_H
