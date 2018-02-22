#include "wContainerSingle.h"

WContainerSingle::WContainerSingle(QObject *parent) : WCacheSingle(parent)
{
    //
}

WContainerSingle::WContainerSingle(const QJsonObject &obj, QObject *parent) : WContainerSingle(parent)
{
    fromJson(obj);
}

QJsonObject WContainerSingle::toJson() const
{
    QJsonObject obj = WCacheSingle::toJson();
    WJson::insert(obj, WJson::Employee_id, QJsonValue(m_employee_id));
    return obj;
}

void WContainerSingle::fromJson(const QJsonObject& obj)
{
    WCacheSingle::fromJson(obj);

    if (WJson::contains(obj, WJson::Employee_id))
        setEmployeeId(WJson::get(obj, WJson::Employee_id).toString());
}

QString WContainerSingle::employeeId() const
{
    return m_employee_id;
}

void WContainerSingle::resetEmployeeId()
{
    setEmployeeId(WStatic::guidDefault());
}

void WContainerSingle::setEmployeeId(QString employee_id)
{
    if (m_employee_id != employee_id){
        m_employee_id = employee_id;
        emit employeeIdChanged(m_employee_id);
    }
}

QDataStream& operator << (QDataStream& s, WContainerSingle& d)
{
    return s << static_cast <WCacheSingle&> (d) << d.m_employee_id;
}

QDataStream& operator >> (QDataStream& s, WContainerSingle& d)
{
    return s >> static_cast <WCacheSingle&> (d) >> d.m_employee_id;
}
