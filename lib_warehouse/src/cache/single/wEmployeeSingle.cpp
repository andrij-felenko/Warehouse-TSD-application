#include "cache/single/wEmployeeSingle.h"
#include <QtCore/QCryptographicHash>
#include "wclass/wJsonConverter.h"

WEmployeeSingle::WEmployeeSingle(QObject *parent) : WCacheSingle(parent)
{
    //
}

WEmployeeSingle::WEmployeeSingle(const QJsonObject &obj, QObject *parent) : WEmployeeSingle(parent)
{
    fromJson(obj);
}

void WEmployeeSingle::fromJson(const QJsonObject &obj)
{
    WCacheSingle::fromJson(obj);

    if (WJsonConverter::contains(obj, WJsonEnum::Password))
        m_password = WJsonConverter::get(obj, WJsonEnum::Password).toString();
    else
        m_password = WStatic::undefined();
}

bool WEmployeeSingle::isCoincide(QString password)
{
    QString hashPassword(QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Md5).toHex());
    return hashPassword == m_password or password == m_password;
}

void WEmployeeSingle::clear()
{
    resetAll();
}

QDataStream& operator << (QDataStream& s, WEmployeeSingle& d)
{
    return s << static_cast <WCacheSingle &> (d) << d.m_password;
}

QDataStream& operator >> (QDataStream& s, WEmployeeSingle& d)
{
    return s >> static_cast <WCacheSingle &> (d) >> d.m_password;
}
