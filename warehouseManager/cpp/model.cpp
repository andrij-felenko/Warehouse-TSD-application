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
    QString modelName("employeeList");
    if (visible)
        WModel::get().registrate(modelName, new ModelCache(modelName, WCache::get().employee(), this));
    else
        WModel::get().removeModel(modelName);
}

void Model::documentList(int key, bool visible)
{
    QString modelName(WUrl::toString(static_cast <WUrl::WUrl_enum>(key)).append("DocumentList"));
    if (visible)
        WModel::get().registrate(modelName, new WModelDocumentList(modelName, WUrl::fromInt(key), this));
    else
        WModel::get().removeModel(modelName);
}

void Model::cacheDocList(QString name, bool visible, QString id, int jsonKey, QVariantMap map)
{
    QString modelName(name.append("CacheDocList"));
    if (visible){
        if (jsonKey != 0 and id != WStatic::guidDefault())
            WModel::get().registrate(modelName, new WModelCacheListByDoc(modelName, WDocument::get().getDocument(id),
                                                                         static_cast <WJson::WJson_enum> (jsonKey),
                                                                         map, this));
    }
    else
        WModel::get().removeModel(modelName);
}
