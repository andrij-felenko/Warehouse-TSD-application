#include "model/wModelPrototype.h"
#include "wSingleton.h"
#include "view/wView.h"
#include "model/wModelCacheList.h"

WModelPrototype::WModelPrototype(QObject *parent)
    : QObject(parent)
{
    nullObject = new QObject(this);
    engine = static_cast <WView*> (parent)->engine();
}

QObject* WModelPrototype::getModel(QString key)
{
    if (model_map.contains(key))
        return model_map[key];
    else
        return nullObject;
}

bool WModelPrototype::registrate(QString key, WModelListTemplate* model, bool insert_anywhat)
{
    if (model_map.contains(key)){
        if (insert_anywhat)
            model_map.value(key)->deleteLater();
        else
            return false;
    }
    engine->setObjectOwnership(model, QQmlEngine::CppOwnership);
    model_map.insert(key, model);
    return true;
}

bool WModelPrototype::removeModel(QObject* obj)
{
    QString key = model_map.key(obj, "null");
    if (key != "null")
        return removeModel(key);
    return false;
}

bool WModelPrototype::removeModel(QString key)
{
    if (model_map.contains(key)){
        model_map.value(key)->deleteLater();
        model_map.remove(key);
        return true;
    }
    return false;
}
