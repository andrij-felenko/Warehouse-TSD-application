#ifndef MODELPROTOTYPE_H
#define MODELPROTOTYPE_H

#include <QtCore/QObject>
#include <QtQml/QQmlEngine>

class ModelPrototype : public QObject
{
    Q_OBJECT
public:
    explicit ModelPrototype(QObject *parent = nullptr);

    bool registrate(QString key, QObject* model, bool insert_anywhat = true);
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
