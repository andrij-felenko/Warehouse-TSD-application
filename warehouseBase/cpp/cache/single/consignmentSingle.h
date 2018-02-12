#ifndef CONSIGNMENTSINGLE_H
#define CONSIGNMENTSINGLE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class ConsignmentSingle : public QObject
{
    Q_OBJECT
public:
    explicit ConsignmentSingle(QObject *parent = nullptr);

signals:

public slots:
};

#endif // CONSIGNMENTSINGLE_H