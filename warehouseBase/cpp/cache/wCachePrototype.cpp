#include "wCachePrototype.h"

WCachePrototype::WCachePrototype(QObject *parent) : QObject(parent)
{
    createLocalDir();

    m_cell         = new WCacheListTemplate <WCellSingle>        (local_dir, "cell",         this);
    m_consignment  = new WCacheListTemplate <WConsignmentSingle> (local_dir, "consignment",  this);
    m_container    = new WCacheListTemplate <WContainerSingle>   (local_dir, "container",    this);
    m_employee     = new WCacheListTemplate <WEmployeeSingle>    (local_dir, "employee",     this);
    m_model_type   = new WCacheListTemplate <WCacheSingle>       (local_dir, "model_type",   this);
    m_nomenclature = new WCacheListTemplate <WNomenclatureSingle>(local_dir, "nomenclature", this);
    m_quality      = new WCacheListTemplate <WQualitySingle>     (local_dir, "quality",      this);
    m_storage_type = new WCacheListTemplate <WCacheSingle>       (local_dir, "storage_type", this);
}

void WCachePrototype::registerType()
{
    //
}

/*! \brief Создание папки для хранений кэша на диске. */
void WCachePrototype::createLocalDir()
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
