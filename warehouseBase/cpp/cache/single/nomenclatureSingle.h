#ifndef NOMENCLATURESINGLE_H
#define NOMENCLATURESINGLE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class NomenclatureSingle : public QObject
{
    Q_OBJECT
public:
    explicit NomenclatureSingle(QObject *parent = nullptr);

signals:

public slots:
};

#endif // NOMENCLATURESINGLE_H