#include "model.h"
#include "wSingleton.h"
#include "enum/wUrl.h"
#include "model/wModelCacheList.h"
#include "model/wModelDocumentList.h"
#include "model/wModelCacheListByDoc.h"

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

void Model::cacheDocList(QString name, bool visible, QString id, int jsonKey, QVariantMap map)
{
    QString model(name.append("CacheDocList"));
    if (visible){
        if (jsonKey != 0 and id != WStatic::guidDefault())
            WModel::get().registrate(model, new WModelCacheListByDoc(WDocument::get().getDocument(id),
                                                                     static_cast <WJson::WJson_enum> (jsonKey),
                                                                     map, this));
    }
    else
        WModel::get().removeModel(model);
}
