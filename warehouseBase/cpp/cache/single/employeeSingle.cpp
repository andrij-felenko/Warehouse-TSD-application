#include "employeeSingle.h"
#include <QtCore/QCryptographicHash>

EmployeeSingle::EmployeeSingle(QObject *parent) : CacheSingle(parent)
{
    //
}

EmployeeSingle::EmployeeSingle(const QJsonObject &obj, QObject *parent) : EmployeeSingle(parent)
{
    fromJson(obj);
}

void EmployeeSingle::fromJson(const QJsonObject &obj)
{
    CacheSingle::fromJson(obj);

    if (WJson::contains(obj, WJson::Password))
        m_password = WJson::get(obj, WJson::Password).toString();
    else
        m_password = WStatic::undefined();
}

bool EmployeeSingle::isCoincide(QString password)
{
    QString hashPassword(QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Md5).toHex());
    return hashPassword == m_password or password == m_password;
}

void EmployeeSingle::clear()
{
    resetAll();
}
