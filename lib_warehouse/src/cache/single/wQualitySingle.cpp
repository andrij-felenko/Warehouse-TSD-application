#include "cache/single/wQualitySingle.h"
#include "wclass/wJsonConverter.h"

WQualitySingle::WQualitySingle(QObject *parent) : WCacheSingle(parent)
{
    //
}

WQualitySingle::WQualitySingle(const QJsonObject &obj, QObject *parent) : WQualitySingle(parent)
{
    fromJson(obj);
}

QJsonObject WQualitySingle::toJson() const
{
    QJsonObject obj = WQualitySingle::toJson();
    WJsonConverter::insert(obj, WJsonEnum::Is_default, QJsonValue(m_isDefault));
    return obj;
}

void WQualitySingle::fromJson(const QJsonObject& obj)
{
    WQualitySingle::fromJson(obj);

    if (WJsonConverter::contains(obj, WJsonEnum::Is_default))
        setIsDefault(WJsonConverter::get(obj, WJsonEnum::Is_default).toBool());
}

bool WQualitySingle::isDefault() const
{
    return m_isDefault;
}

void WQualitySingle::resetIsDefault()
{
    setIsDefault(false);
}

void WQualitySingle::setIsDefault(bool isDefault)
{
    if (m_isDefault != isDefault){
        m_isDefault = isDefault;
        emit isDefaultChanged(m_isDefault);
    }
}

QDataStream& operator << (QDataStream& s, WQualitySingle& d)
{
    return s << static_cast <WCacheSingle&> (d) << d.m_isDefault;
}

QDataStream& operator >> (QDataStream& s, WQualitySingle& d)
{
    return s >> static_cast <WCacheSingle&> (d) >> d.m_isDefault;
}
