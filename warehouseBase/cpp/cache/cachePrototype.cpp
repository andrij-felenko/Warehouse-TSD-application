#include "cachePrototype.h"

CachePrototype::CachePrototype(QObject *parent) : QObject(parent)
{
    createLocalDir();

    m_cell         = new CacheListTemplate <CacheSingle>(local_dir, "cell",         this);
    m_consignment  = new CacheListTemplate <CacheSingle>(local_dir, "consignment",  this);
    m_container    = new CacheListTemplate <CacheSingle>(local_dir, "container",    this);
    m_employee     = new CacheListTemplate <CacheSingle>(local_dir, "employee",     this);
    m_model_type   = new CacheListTemplate <CacheSingle>(local_dir, "model_type",   this);
    m_nomenclature = new CacheListTemplate <CacheSingle>(local_dir, "nomenclature", this);
    m_quality      = new CacheListTemplate <CacheSingle>(local_dir, "quality",      this);
    m_storage_type = new CacheListTemplate <CacheSingle>(local_dir, "storage_type", this);
}

void CachePrototype::registerType()
{
    //
}

/*! \brief Создание папки для хранений кэша на диске. */
void CachePrototype::createLocalDir()
{
    QDir dir(QDir::home());
#ifdef Q_OS_UNIX
    QString path = ".warehouse_manager";
#elif Q_OS_WINDOWS
    QString path = "warehouse_manager";
#endif
    dir.mkdir(path);
    dir.cd(path);
    local_dir = dir;
}
