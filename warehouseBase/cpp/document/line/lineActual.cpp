#include "lineActual.h"
#include "singleton.h"

LineActual::LineActual(QObject *parent) : LinePlan(parent)
{
    QObject::connect(Cache::get().employee(), &CacheListObject::listPushed,  this, &LineActual::updateEmployee);
    QObject::connect(Cache::get().employee(), &CacheListObject::listUpdated, this, &LineActual::updateEmployee);

    resetAll();
}

LineActual::LineActual(const QJsonObject& obj, QObject* parent) : LineActual(parent)
{
    fromJson(obj);
}

QJsonObject LineActual::toJson() const
{
    auto obj = LinePlan::toJson();
    WJson::insert(obj, WJson::Line_id, m_lineId);
    WJson::insert(obj, WJson::Is_done, m_isDone);
    WJson::insert(obj, WJson::Employee_id,   m_employeeId);
    WJson::insert(obj, WJson::Employee_name, m_employeeName);
    return obj;
}

void LineActual::fromJson(const QJsonObject& obj)
{
    if (WJson::contains(obj, WJson::Is_done))
        setIsDone(WJson::get(obj, WJson::Is_done).toBool());

    // Line number
    if (WJson::contains(obj, WJson::Line_id))
        setLineId(WJson::get(obj, WJson::Line_id).toString());

    // Consignment
    if (WJson::contains(obj, WJson::Employee_id))
        setEmployeeId(WJson::get(obj, WJson::Employee_id).toString());

    if (WJson::contains(obj, WJson::Employee_name))
        setEmployeeName(WJson::get(obj, WJson::Employee_name).toString());
    else
        updateEmployeeName();
}

void LineActual::setIsDone(bool isDone)
{
    if (m_isDone != isDone){
        m_isDone = isDone;
        emit isDoneChanged(m_isDone);
    }
}

void LineActual::setLineId(QString lineId)
{
    if (m_lineId != lineId){
        m_lineId = lineId;
        emit lineIdChanged(m_lineId);
    }
}

void LineActual::setEmployeeId(QString employeeId)
{
    if (m_employeeId != employeeId){
        m_employeeId = employeeId;
        emit employeeIdChanged(m_employeeId);
        updateEmployeeName();
    }
}

void LineActual::setEmployeeName(QString employeeName)
{
    if (m_employeeName != employeeName){
        m_employeeName = employeeName;
        emit employeeNameChanged(m_employeeName);
    }
}

void LineActual::updateEmployee(QStringList list)
{
    if (list.contains(m_employeeId))
        updateEmployeeName();
}

void LineActual::updateEmployeeName()
{
    setEmployeeName(Cache::get().employee()->getNameById(m_employeeId));
}

void LineActual::resetAll()
{
    LinePlan::resetAll();
    resetLineId();
    resetIsDone();
    resetEmployeeName();
    resetEmployeeId();
}
