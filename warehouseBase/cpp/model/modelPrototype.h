#ifndef MODELPROTOTYPE_H
#define MODELPROTOTYPE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class ModelPrototype : public QObject
{
    Q_OBJECT
public:
    explicit ModelPrototype(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MODELPROTOTYPE_H