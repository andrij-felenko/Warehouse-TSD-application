#ifndef SERVERPROTOTYPE_H
#define SERVERPROTOTYPE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class ServerPrototype : public QObject
{
    Q_OBJECT
public:
    explicit ServerPrototype(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SERVERPROTOTYPE_H