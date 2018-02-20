#ifndef EMPLOYEESINGLE_H
#define EMPLOYEESINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wjson.h"
#include "enum/wstatic.h"
#include "cacheSingle.h"

class EmployeeSingle : public CacheSingle
{
    Q_OBJECT
public:
    explicit EmployeeSingle(QObject *parent = nullptr);
    EmployeeSingle(const QJsonObject& obj, QObject* parent = nullptr);

    // Json ----------------------------------------------------------------------------------------
    void fromJson(const QJsonObject& obj);

    bool isCoincide(QString password);
    void clear();

private:
    QString m_password;
};

#endif // EMPLOYEESINGLE_H
