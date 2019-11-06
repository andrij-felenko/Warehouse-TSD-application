#ifndef WLINEACTUAL_H
#define WLINEACTUAL_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "wLinePlan.h"

class WLineActual : public WLinePlan
{
    Q_OBJECT
    Q_PROPERTY(QString lineId     READ lineId     WRITE setLineId     RESET resetLineId     NOTIFY lineIdChanged)
    Q_PROPERTY(QString employeeId READ employeeId WRITE setEmployeeId RESET resetEmployeeId NOTIFY employeeIdChanged)
    Q_PROPERTY(QString employeeName READ       employeeName WRITE setEmployeeName
                                    RESET resetEmployeeName NOTIFY   employeeNameChanged)

public:
    explicit WLineActual(QObject *parent = nullptr);
    WLineActual(const QJsonObject& obj, QObject* parent = nullptr);

    // JSON ---------------------------------------------------------------------------------------
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

    // READ ---------------------------------------------------------------------------------------
    QString lineId()       const { return m_lineId; }
    QString employeeId()   const { return m_employeeId; }
    QString employeeName() const { return m_employeeName; }

    // RESET --------------------------------------------------------------------------------------
    void resetLineId()       { setLineId(WStatic::guidCreate()); }
    void resetEmployeeId()   { setEmployeeId(WStatic::guidDefault()); }
    void resetEmployeeName() { setEmployeeName(WStatic::undefined()); }
    void clear()             { resetAll(); }

signals:
    void lineIdChanged(QString lineId);
    void employeeIdChanged  (QString employeeId);
    void employeeNameChanged(QString employeeName);

public slots:
    void setLineId(QString lineId);
    void setEmployeeId(QString employeeId);

protected:
    void resetAll();

private:
    QString m_lineId;
    QString m_employeeId;
    QString m_employeeName;

    // WRITE NAME PRIVATE -------------------------------------------------------------------------
    void setEmployeeName(QString employeeName);
    void updateEmployee(QStringList list);
    void updateEmployeeName();
};

#endif // LINEACTUAL_H
