#include "document/line/wLineActual.h"
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
    WJsonConverter::insert(obj, WJsonEnum::Line_id, m_lineId);
    WJsonConverter::insert(obj, WJsonEnum::Employee_id,   m_employeeId);
    WJsonConverter::insert(obj, WJsonEnum::Employee_name, m_employeeName);
    return obj;
}

void WLineActual::fromJson(const QJsonObject& obj)
{
    // Line id
    if (WJsonConverter::contains(obj, WJsonEnum::Line_id))
        setLineId(WJsonConverter::get(obj, WJsonEnum::Line_id).toString());

    // Employee
    if (WJsonConverter::contains(obj, WJsonEnum::Employee_id))
        setEmployeeId(WJsonConverter::get(obj, WJsonEnum::Employee_id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Employee_name))
        setEmployeeName(WJsonConverter::get(obj, WJsonEnum::Employee_name).toString());
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
