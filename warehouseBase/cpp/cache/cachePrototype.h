#ifndef CACHEPROTOTYPE_H
#define CACHEPROTOTYPE_H

#include <QtCore/QDir>
#include <QtCore/QObject>
#include <QtQml/QQmlEngine>

#include "single/cacheSingle.h"
#include "template/cacheListTemplate.h"

///< Общий клас для управления всем кэшем.
class CachePrototype : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CacheListTemplate <CacheSingle>* cell         READ cell)
    Q_PROPERTY(CacheListTemplate <CacheSingle>* consignment  READ consignment)
    Q_PROPERTY(CacheListTemplate <CacheSingle>* container    READ container)
    Q_PROPERTY(CacheListTemplate <CacheSingle>* employee     READ employee)
    Q_PROPERTY(CacheListTemplate <CacheSingle>* model_type   READ model_type)
    Q_PROPERTY(CacheListTemplate <CacheSingle>* nomenclature READ nomenclature)
    Q_PROPERTY(CacheListTemplate <CacheSingle>* quality      READ quality)
    Q_PROPERTY(CacheListTemplate <CacheSingle>* storage_type READ storage_type)

public:
    explicit CachePrototype(QObject *parent = nullptr);

    void registerType();

    CacheListTemplate <CacheSingle>* cell()         const { return m_cell; }
    CacheListTemplate <CacheSingle>* consignment()  const { return m_consignment; }
    CacheListTemplate <CacheSingle>* container()    const { return m_container; }
    CacheListTemplate <CacheSingle>* employee()     const { return m_employee; }
    CacheListTemplate <CacheSingle>* model_type()   const { return m_model_type; }
    CacheListTemplate <CacheSingle>* nomenclature() const { return m_nomenclature; }
    CacheListTemplate <CacheSingle>* quality()      const { return m_quality; }
    CacheListTemplate <CacheSingle>* storage_type() const { return m_storage_type; }

private:
    inline void createLocalDir();
    QDir local_dir; ///< Директория для хранения кэша.

    CacheListTemplate <CacheSingle>* m_cell;
    CacheListTemplate <CacheSingle>* m_consignment;
    CacheListTemplate <CacheSingle>* m_container;
    CacheListTemplate <CacheSingle>* m_employee;
    CacheListTemplate <CacheSingle>* m_model_type;
    CacheListTemplate <CacheSingle>* m_nomenclature;
    CacheListTemplate <CacheSingle>* m_quality;
    CacheListTemplate <CacheSingle>* m_storage_type;
};

#endif // CACHEPROTOTYPE_H
