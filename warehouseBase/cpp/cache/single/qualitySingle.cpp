#include "qualitySingle.h"

QualitySingle::QualitySingle(QObject *parent) : QObject(parent)
{
    //
}

QualitySingle::QualitySingle(const QJsonObject &obj, QObject *parent) : QualitySingle(parent)
{
    fromJson(obj);
}

QJsonObject QualitySingle::toJson() const
{
    QJsonObject obj = QualitySingle::toJson();
    WJson::insert(obj, WJson::Is_default, QJsonValue(m_isDefault));
    return obj;
}

void QualitySingle::fromJson(const QJsonObject& obj)
{
    QualitySingle::fromJson(obj);

    if (WJson::contains(obj, WJson::Is_default))
        setIsDefault(WJson::get(obj, WJson::Is_default).toBool());
}

bool QualitySingle::isDefault() const
{
    return m_isDefault;
}

void QualitySingle::resetIsDefault()
{
    setIsDefault(false);
}

void QualitySingle::setIsDefault(bool isDefault)
{
    if (m_isDefault != isDefault){
        m_isDefault = isDefault;
        emit isDefaultChanged(m_isDefault);
    }
}
