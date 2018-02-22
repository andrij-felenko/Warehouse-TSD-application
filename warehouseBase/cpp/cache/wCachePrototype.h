#ifndef CACHEPROTOTYPE_H
#define CACHEPROTOTYPE_H

#include <QtCore/QDir>
#include <QtCore/QObject>
#include <QtQml/QQmlEngine>

#include "single/wCacheSingle.h"
#include "single/wCellSingle.h"
#include "single/wConsignmentSingle.h"
#include "single/wContainerSingle.h"
#include "single/wEmployeeSingle.h"
#include "single/wNomenclatureSingle.h"
#include "single/wQualitySingle.h"
#include "template/wCacheListTemplate.h"

///< Общий клас для управления всем кэшем.
class WCachePrototype : public QObject
{
    Q_OBJECT
    Q_PROPERTY(WCacheListTemplate <WCellSingle>*         cell         READ cell)
    Q_PROPERTY(WCacheListTemplate <WConsignmentSingle>*  consignment  READ consignment)
    Q_PROPERTY(WCacheListTemplate <WContainerSingle>*    container    READ container)
    Q_PROPERTY(WCacheListTemplate <WEmployeeSingle>*     employee     READ employee)
    Q_PROPERTY(WCacheListTemplate <WCacheSingle>*        model_type   READ model_type)
    Q_PROPERTY(WCacheListTemplate <WNomenclatureSingle>* nomenclature READ nomenclature)
    Q_PROPERTY(WCacheListTemplate <WQualitySingle>*      quality      READ quality)
    Q_PROPERTY(WCacheListTemplate <WCacheSingle>*        storage_type READ storage_type)

public:
    explicit WCachePrototype(QObject *parent = nullptr);

    void registerType();

    WCacheListTemplate <WCellSingle>*         cell()         const { return m_cell; }
    WCacheListTemplate <WConsignmentSingle>*  consignment()  const { return m_consignment; }
    WCacheListTemplate <WContainerSingle>*    container()    const { return m_container; }
    WCacheListTemplate <WEmployeeSingle>*     employee()     const { return m_employee; }
    WCacheListTemplate <WCacheSingle>*        model_type()   const { return m_model_type; }
    WCacheListTemplate <WNomenclatureSingle>* nomenclature() const { return m_nomenclature; }
    WCacheListTemplate <WQualitySingle>*      quality()      const { return m_quality; }
    WCacheListTemplate <WCacheSingle>*        storage_type() const { return m_storage_type; }

private:
    inline void createLocalDir();
    QDir local_dir; ///< Директория для хранения кэша.

    WCacheListTemplate <WCellSingle>* m_cell;
    WCacheListTemplate <WConsignmentSingle>* m_consignment;
    WCacheListTemplate <WContainerSingle>* m_container;
    WCacheListTemplate <WEmployeeSingle>* m_employee;
    WCacheListTemplate <WCacheSingle>* m_model_type;
    WCacheListTemplate <WNomenclatureSingle>* m_nomenclature;
    WCacheListTemplate <WQualitySingle>* m_quality;
    WCacheListTemplate <WCacheSingle>* m_storage_type;
};

#endif // CACHEPROTOTYPE_H
