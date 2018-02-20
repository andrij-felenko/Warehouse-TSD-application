#include "whmodel.h"
#include "singleton.h"
#include "model/modelCacheList.h"

WHModel::WHModel(QObject *parent) : QObject(parent)
{
    //
}

void WHModel::employeeList(bool visible)
{
    if (visible)
        Model::get().registrate("employeeList",
                                new ModelCacheList <CacheListTemplate <CacheSingle>> (Cache::get().employee()));
    else
        Model::get().removeModel("employeeList");
}
