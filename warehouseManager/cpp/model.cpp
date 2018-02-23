#include "model.h"
#include "wSingleton.h"
#include "enum/wUrl.h"
#include "model/wModelCacheList.h"
#include "model/wModelDocumentList.h"

Model::Model(QObject *parent) : QObject(parent)
{
    //
}

void Model::employeeList(bool visible)
{
    typedef WModelCacheList <WCacheListTemplate <WEmployeeSingle>> ModelCache;
    if (visible)
        WModel::get().registrate("employeeList", new ModelCache(WCache::get().employee(), this));
    else
        WModel::get().removeModel("employeeList");
}

void Model::documentList(int key, bool visible)
{
    QString model(WUrl::toString(static_cast <WUrl::WUrl_enum>(key)).append("DocumentList"));
    if (visible)
        WModel::get().registrate(model, new WModelDocumentList(WUrl::fromInt(key), this));
    else
        WModel::get().removeModel(model);
}
