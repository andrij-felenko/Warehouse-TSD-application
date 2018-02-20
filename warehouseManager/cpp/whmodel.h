#ifndef WHMODEL_H
#define WHMODEL_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class WHModel : public QObject
{
    Q_OBJECT
public:
    explicit WHModel(QObject *parent = nullptr);

signals:

public slots:
    void employeeList(bool visible);
};

#endif // WHMODEL_H
