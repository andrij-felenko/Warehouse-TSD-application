#include "whmodel.h"
#include "wSingleton.h"
#include "enum/wurl.h"
#include "model/wModelCacheList.h"
#include "model/wModelDocumentList.h"

WHModel::WHModel(QObject *parent) : QObject(parent)
{
    //
}

void WHModel::employeeList(bool visible)
{
    typedef WModelCacheList <WCacheListTemplate <WEmployeeSingle>> ModelCache;
    if (visible)
        WModel::get().registrate("employeeList", new ModelCache(WCache::get().employee(), this));
    else
        WModel::get().removeModel("employeeList");
}

void WHModel::documentList(int key, bool visible)
{
    qDebug() << key << (+WUrl::Receiving);
    QString model(WUrl::toString(static_cast <WUrl::WUrl_enum>(key)).append("DocumentList"));
    if (visible)
        qDebug() << model << WModel::get().registrate(model, new WModelDocumentList(WUrl::fromInt(key), this));
    else
        WModel::get().removeModel(model);
}
