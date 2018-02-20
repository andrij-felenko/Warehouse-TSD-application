#include "modelPrototype.h"
#include "singleton.h"
#include "view/view.h"
#include "modelCacheList.h"

ModelPrototype::ModelPrototype(QObject *parent)
    : QObject(parent)
{
    nullObject = new QObject(this);
    engine = static_cast <View*> (parent)->engine();
}

QObject* ModelPrototype::getModel(QString key)
{
    if (model_map.contains(key))
        return model_map[key];
    else
        return nullObject;
}

bool ModelPrototype::registrate(QString key, QObject* model, bool insert_anywhat)
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

bool ModelPrototype::removeModel(QObject* obj)
{
    QString key = model_map.key(obj, "null");
    if (key != "null")
        return removeModel(key);
    return false;
}

bool ModelPrototype::removeModel(QString key)
{
    if (model_map.contains(key)){
        model_map.value(key)->deleteLater();
        model_map.remove(key);
        return true;
    }
    return false;
}
