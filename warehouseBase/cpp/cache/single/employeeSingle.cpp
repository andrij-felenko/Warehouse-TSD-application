#include "employeeSingle.h"

EmployeeSingle::EmployeeSingle(QObject *parent) : CacheSingle(parent)
{
    //
}

EmployeeSingle::EmployeeSingle(const QJsonObject &obj, QObject *parent) : EmployeeSingle(parent)
{
    fromJson(obj);
}

void EmployeeSingle::fromJson(const QJsonObject &obj)
{
    CacheSingle::fromJson(obj);

    if (WJson::contains(obj, WJson::Password)){
        m_password = WJson::get(obj, WJson::Password).toString();
        emit passwordChanged(m_password);
    }
    else
        m_password = WStatic::undefined();
}

QString EmployeeSingle::password() const
{
    return m_password;
}
