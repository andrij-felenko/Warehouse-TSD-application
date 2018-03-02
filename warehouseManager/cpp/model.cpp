#include "model.h"
#include "wSingleton.h"
#include "enum/wUrlEnum.h"
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
    QString modelName(WUrlConverter::toString(static_cast <WUrlEnum::WUrl_enum>(key)).append("DocumentList"));
    if (visible)
        WModel::get().registrate(modelName, new WModelDocumentList(modelName, WUrlConverter::fromInt(key), this));
    else
        WModel::get().removeModel(modelName);
}

void Model::cacheDocList(QString name, bool visible, QString id, int jsonKey, QVariantMap map)
{
    QString modelName(name.append("CacheDocList"));
    if (visible){
        if (jsonKey != 0 and id != WStatic::guidDefault())
            WModel::get().registrate(modelName, new WModelCacheListByDoc(modelName, WDocument::get().getDocument(id),
                                                                         static_cast <WJsonEnum::WJson_enum> (jsonKey),
                                                                         map, this));
    }
    else
        WModel::get().removeModel(modelName);
}
