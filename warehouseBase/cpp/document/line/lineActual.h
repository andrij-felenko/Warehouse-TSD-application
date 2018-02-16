#ifndef LINEACTUAL_H
#define LINEACTUAL_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "linePlan.h"

class LineActual : public LinePlan
{
    Q_OBJECT
    Q_PROPERTY(bool    isDone     READ isDone     WRITE setIsDone     RESET resetIsDone     NOTIFY isDoneChanged)
    Q_PROPERTY(QString lineId     READ lineId     WRITE setLineId     RESET resetLineId     NOTIFY lineIdChanged)
    Q_PROPERTY(QString employeeId READ employeeId WRITE setEmployeeId RESET resetEmployeeId NOTIFY employeeIdChanged)
    Q_PROPERTY(QString employeeName READ       employeeName WRITE setEmployeeName
                                    RESET resetEmployeeName NOTIFY   employeeNameChanged)

public:
    explicit LineActual(QObject *parent = nullptr);
    LineActual(const QJsonObject& obj, QObject* parent = nullptr);

    // JSON ---------------------------------------------------------------------------------------
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

    // READ ---------------------------------------------------------------------------------------
    bool    isDone()       const { return m_isDone; }
    QString lineId()       const { return m_lineId; }
    QString employeeId()   const { return m_employeeId; }
    QString employeeName() const { return m_employeeName; }

    // RESET --------------------------------------------------------------------------------------
    void resetIsDone()       { setIsDone(false); }
    void resetLineId()       { setLineId(WStatic::guidCreate()); }
    void resetEmployeeId()   { setEmployeeId(WStatic::guidDefault()); }
    void resetEmployeeName() { setEmployeeName(WStatic::undefined()); }

signals:
    void isDoneChanged(bool isDone);
    void lineIdChanged(QString lineId);
    void employeeIdChanged  (QString employeeId);
    void employeeNameChanged(QString employeeName);

public slots:
    void setIsDone(bool isDone);
    void setLineId(QString lineId);
    void setEmployeeId(QString employeeId);

protected:
    void resetAll();

private:
    bool m_isDone;
    QString m_lineId;
    QString m_employeeId;
    QString m_employeeName;

    // WRITE NAME PRIVATE -------------------------------------------------------------------------
    void setEmployeeName(QString employeeName);
    void updateEmployee(QStringList list);
    void updateEmployeeName();
};

#endif // LINEACTUAL_H