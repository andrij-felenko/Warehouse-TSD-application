#ifndef WCURRENTUSER_H
#define WCURRENTUSER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "cache/single/wEmployeeSingle.h"

class WCurrentUser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(WEmployeeSingle* current READ current NOTIFY currentChanged)

public:
    explicit WCurrentUser(QObject *parent = nullptr);

    WEmployeeSingle* current() const { return m_current; }

signals:
    void currentChanged(WEmployeeSingle* current);

public slots:
    void setUserInput(QString line);
    void setUserList(QString id);
    bool tryAuthorization(QString password);

private:
    WEmployeeSingle* m_current;
};

#endif // CURRENTUSER_H
