#ifndef CURRENTUSER_H
#define CURRENTUSER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "cache/single/employeeSingle.h"

class CurrentUser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(EmployeeSingle* current READ current NOTIFY currentChanged)

public:
    explicit CurrentUser(QObject *parent = nullptr);

    EmployeeSingle* current() const { return m_current; }

signals:
    void currentChanged(EmployeeSingle* current);

public slots:
    void setUserInput(QString line);
    void setUserList(QString id);

private:
    EmployeeSingle* m_current;
};

#endif // CURRENTUSER_H
