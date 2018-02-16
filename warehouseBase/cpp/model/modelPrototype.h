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
    bool remove_model(QObject* obj);
    bool remove_model(QString key);

private:
    QMap <QString /*key*/, QObject* /*model*/> model_map;
    QQmlEngine* engine;

public slots:
    QObject* get_model(QString key);
};

#endif // MODELPROTOTYPE_H
