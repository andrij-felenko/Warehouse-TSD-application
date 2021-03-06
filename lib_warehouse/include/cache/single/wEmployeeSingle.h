#ifndef WEMPLOYEESINGLE_H
#define WEMPLOYEESINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wJsonEnum.h"
#include "wclass/wStatic.h"
#include "wCacheSingle.h"

class WEmployeeSingle : public WCacheSingle
{
    Q_OBJECT
public:
    explicit WEmployeeSingle(QObject *parent = nullptr);
    WEmployeeSingle(const QJsonObject& obj, QObject* parent = nullptr);
    operator WCacheSingle* () { return reinterpret_cast <WCacheSingle*> (this); }

    // Json ----------------------------------------------------------------------------------------
    void fromJson(const QJsonObject& obj);

    bool isCoincide(QString password);
    void clear();

protected:
    friend QDataStream& operator << (QDataStream &s, WEmployeeSingle& d);
    friend QDataStream& operator >> (QDataStream &s, WEmployeeSingle& d);

private:
    QString m_password;
};

#endif // EMPLOYEESINGLE_H
