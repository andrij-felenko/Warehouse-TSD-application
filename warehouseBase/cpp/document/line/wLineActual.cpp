#include "wLineActual.h"
#include "wSingleton.h"

WLineActual::WLineActual(QObject *parent) : WLinePlan(parent)
{
    QObject::connect(WCache::get().employee(), &WCacheListObject::listPushed,  this, &WLineActual::updateEmployee);
    QObject::connect(WCache::get().employee(), &WCacheListObject::listUpdated, this, &WLineActual::updateEmployee);

    resetAll();
}

WLineActual::WLineActual(const QJsonObject& obj, QObject* parent) : WLineActual(parent)
{
    fromJson(obj);
}

QJsonObject WLineActual::toJson() const
{
    auto obj = WLinePlan::toJson();
    WJson::insert(obj, WJson::Line_id, m_lineId);
    WJson::insert(obj, WJson::Employee_id,   m_employeeId);
    WJson::insert(obj, WJson::Employee_name, m_employeeName);
    return obj;
}

void WLineActual::fromJson(const QJsonObject& obj)
{
    // Line id
    if (WJson::contains(obj, WJson::Line_id))
        setLineId(WJson::get(obj, WJson::Line_id).toString());

    // Employee
    if (WJson::contains(obj, WJson::Employee_id))
        setEmployeeId(WJson::get(obj, WJson::Employee_id).toString());

    if (WJson::contains(obj, WJson::Employee_name))
        setEmployeeName(WJson::get(obj, WJson::Employee_name).toString());
    else
        updateEmployeeName();
}

void WLineActual::setLineId(QString lineId)
{
    if (m_lineId != lineId){
        m_lineId = lineId;
        emit lineIdChanged(m_lineId);
    }
}

void WLineActual::setEmployeeId(QString employeeId)
{
    if (m_employeeId != employeeId){
        m_employeeId = employeeId;
        emit employeeIdChanged(m_employeeId);
        updateEmployeeName();
    }
}

void WLineActual::setEmployeeName(QString employeeName)
{
    if (m_employeeName != employeeName){
        m_employeeName = employeeName;
        emit employeeNameChanged(m_employeeName);
    }
}

void WLineActual::updateEmployee(QStringList list)
{
    if (list.contains(m_employeeId))
        updateEmployeeName();
}

void WLineActual::updateEmployeeName()
{
    setEmployeeName(WCache::get().employee()->getNameById(m_employeeId));
}

void WLineActual::resetAll()
{
    WLinePlan::resetAll();
    resetLineId();
    resetIsDone();
    resetEmployeeName();
    resetEmployeeId();
}
