#include "wCachePrototype.h"
#include "wSingleton.h"
#include "server/wRequestGenerate.h"

WCachePrototype::WCachePrototype(QObject *parent) : QObject(parent)
{
    createLocalDir();

    m_cell         = new WCacheListTemplate <WCellSingle>        (m_local_dir, "cell",         this);
    m_consignment  = new WCacheListTemplate <WConsignmentSingle> (m_local_dir, "consignment",  this);
    m_container    = new WCacheListTemplate <WContainerSingle>   (m_local_dir, "container",    this);
    m_employee     = new WCacheListTemplate <WEmployeeSingle>    (m_local_dir, "employee",     this);
    m_model_type   = new WCacheListTemplate <WCacheSingle>       (m_local_dir, "model_type",   this);
    m_nomenclature = new WCacheListTemplate <WNomenclatureSingle>(m_local_dir, "nomenclature", this);
    m_quality      = new WCacheListTemplate <WQualitySingle>     (m_local_dir, "quality",      this);
    m_storage_type = new WCacheListTemplate <WCacheSingle>       (m_local_dir, "storage_type", this);

    m_allCacheTimer = new QTimer(this);
    m_allCacheTimer->setInterval(5 /* minute */ * 60 /* sec */ * 1000 /* ms */);
    QObject::connect(m_allCacheTimer, &QTimer::timeout, this, &WCachePrototype::updateAllCache);

    m_quequeTimer = new QTimer(this);
    m_quequeTimer->setInterval(2 /* sec */ * 1000 /* ms */);
    QObject::connect(m_quequeTimer, &QTimer::timeout, this, &WCachePrototype::updateCache);

    updateAllCache();
}

void WCachePrototype::pushCacheToQueque(WUrl::WUrl_enum key, QStringList list)
{
    for (auto it : list)
        if (it != WStatic::guidDefault())
            if (it != WStatic::guidNull()){
                bool isFound(false);
                for (auto cit : m_cacheUpdateList)
                    if (cit == it){
                        isFound = true;
                        break;
                    }
                if (not isFound)
                    m_cacheUpdateList.insert(key, it);
            }
}

WCacheSingle* WCachePrototype::getOne(QString id, WJson::WJson_enum key)
{
    switch (key) {
    case WJson::Cell_id:
    case WJson::Cell_receiver_id:
    case WJson::Cell_sender_id:
        return m_cell->getOne(id);
    case WJson::Consignment:
    case WJson::Consignment_id:
        return m_consignment->getOne(id);
    case WJson::Container_id:
    case WJson::Container_receiver_id:
    case WJson::Container_sender_id:
        return m_container->getOne(id);
    case WJson::Employee_id:
        return m_employee->getOne(id);
    case WJson::ModelTypeId:
        return m_model_type->getOne(id);
    case WJson::Nomenclature_id:
        return m_nomenclature->getOne(id);
    case WJson::Quality_id:
        return m_quality->getOne(id);
//    case WJson::Warehouse_id:
//    case WJson::Warehouse_receiver_id:
//    case WJson::Warehouse_sender_id:
//        return m_ware
    default:;
    }
    return nullptr;
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
    m_local_dir = dir;
}

void WCachePrototype::updateCacheByKey(WUrl::WUrl_enum key)
{
    QStringList list;
    for (auto it = m_cacheUpdateList.begin(); it != m_cacheUpdateList.end(); ++it)
        if (it.key() == key)
            list.push_back(it.value());
    if (list.isEmpty())
        return;

    WServer::get().request(WUrl::compareUrl({ WUrl::Get, key, WUrl::By, WUrl::Id }),
                           QObject::tr("Обновить список ячеек."),
                           WRequestGenerate::list(list));
}

void WCachePrototype::updateCache()
{
    updateCacheByKey(WUrl::Cell);
    updateCacheByKey(WUrl::Consignment);
    updateCacheByKey(WUrl::Container);
    updateCacheByKey(WUrl::Nomenclature);

    m_cacheUpdateList.clear();
}

void WCachePrototype::updateAllCache()
{
    updateCache();

    WServer::get().request(WUrl::compareUrl({ WUrl::Update, WUrl::Cell, WUrl::Cache }),
                           QObject::tr("Обновить список ячеек."),
                           WRequestGenerate::date(m_cell->dateTime()));

    WServer::get().request(WUrl::compareUrl({ WUrl::Update, WUrl::Consignment, WUrl::Cache }),
                           QObject::tr("Обновить список партий."),
                           WRequestGenerate::date(m_consignment->dateTime()));

    WServer::get().request(WUrl::compareUrl({ WUrl::Update, WUrl::Container, WUrl::Cache }),
                           QObject::tr("Обновить список контейнеров."),
                           WRequestGenerate::date(m_container->dateTime()));

    WServer::get().request(WUrl::compareUrl({ WUrl::Get, WUrl::Employee, WUrl::List }),
                           QObject::tr("Обновить список пользователей."),
                           WRequestGenerate::empty(), WEnum::Request_must_server);

    WServer::get().request(WUrl::compareUrl({ WUrl::Update, WUrl::Model, WUrl::Type, WUrl::Cache }),
                           QObject::tr("Обновить список моделей учета."),
                           WRequestGenerate::date(m_model_type->dateTime()));

    WServer::get().request(WUrl::compareUrl({ WUrl::Update, WUrl::Nomenclature, WUrl::Cache }),
                           QObject::tr("Обновить список номенклатур."),
                           WRequestGenerate::date(m_nomenclature->dateTime()));

    WServer::get().request(WUrl::compareUrl({ WUrl::Update, WUrl::Quality, WUrl::List }),
                           QObject::tr("Обновить список качеств."),
                           WRequestGenerate::empty());

    WServer::get().request(WUrl::compareUrl({ WUrl::Update, WUrl::Storage, WUrl::Unit, WUrl::List }),
                           QObject::tr("Обновить список типов хранения."),
                           WRequestGenerate::empty());
}
