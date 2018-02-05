#include "containersingle.h"

ContainerSingle::ContainerSingle(QObject *parent) : CacheSingle(parent)
{
    //
}

ContainerSingle::ContainerSingle(const QJsonObject &obj, QObject *parent) : ContainerSingle(parent)
{
    fromJson(obj);
}

QJsonObject ContainerSingle::toJson() const
{
    QJsonObject obj = CacheSingle::toJson();
    WJson::insert(obj, WJson::Employee_id, QJsonValue(m_employee_id));
    return obj;
}

void ContainerSingle::fromJson(const QJsonObject& obj)
{
    CacheSingle::fromJson(obj);

    if (WJson::contains(obj, WJson::Employee_id))
        setEmployeeId(WJson::get(obj, WJson::Employee_id).toString());
}

QString ContainerSingle::employeeId() const
{
    return m_employee_id;
}

void ContainerSingle::resetEmployeeId()
{
    setEmployeeId(WStatic::guidDefault());
}

void ContainerSingle::setEmployeeId(QString employee_id)
{
    if (m_employee_id != employee_id){
        m_employee_id = employee_id;
        emit employeeIdChanged(m_employee_id);
    }
}
