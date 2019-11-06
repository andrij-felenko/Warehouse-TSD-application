#ifndef WMODELPROTOTYPE_H
#define WMODELPROTOTYPE_H

#include <QtCore/QObject>
#include <QtQml/QQmlEngine>
#include "template/wModelListTemplate.h"

class WModelPrototype : public QObject
{
    Q_OBJECT
public:
    explicit WModelPrototype(QObject *parent = nullptr);

    bool registrate(QString key, WModelListTemplate* model, bool insert_anywhat = true);
    bool removeModel(QObject* obj);
    bool removeModel(QString key);

public slots:
    QObject* getModel(QString key);

private:
    QMap <QString /*key*/, QObject* /*model*/> model_map;
    QQmlEngine* engine;
    QObject* nullObject;
};

#endif // MODELPROTOTYPE_H
