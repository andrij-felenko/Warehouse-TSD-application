#include "cacheSingle.h"

/*!
 * \brief По умолчанию.
 * \param parent ссылка на родительский обьект
 */
CacheSingle::CacheSingle(QObject* parent) : QObject(parent)
{
    resetAll();
}

/*!
 * \brief Создание обьекта с json-обьекта.
 * \details Сначала вызываеться конструктор по умолчанию, после этого переменным присваиваються
 * значение с json обьектов.
 * \param obj json-обьект, по данным которого создаеться обьект
 * \param parent ссылка на родительский обьект
 */
CacheSingle::CacheSingle(const QJsonObject& obj, QObject* parent) : CacheSingle(parent)
{
    fromJson(obj);
}

QJsonObject CacheSingle::toJson() const
{
    QJsonObject obj;
    Json::insert(obj, Json::Id,      m_id);
    Json::insert(obj, Json::Name,    m_name);
    Json::insert(obj, Json::Barcode, m_barcode);
    return obj;
}

void CacheSingle::fromJson(const QJsonObject& obj)
{
    resetAll();
    if (Json::contains(obj, Json::Id))      setId     (Json::get(obj, Json::Id)     .toString());
    if (Json::contains(obj, Json::Name))    setName   (Json::get(obj, Json::Name)   .toString());
    if (Json::contains(obj, Json::Barcode)) setBarcode(Json::get(obj, Json::Barcode).toString());
}

void CacheSingle::resetAll()
{
    resetBarcode();
    resetId();
    resetName();
}

void CacheSingle::setId(QString id)
{
    if (m_id != id){
        m_id = id;
        emit idChanged(m_id);
    }
}

void CacheSingle::setName(QString name)
{
    if (m_name != name){
        m_name = name;
        emit nameChanged(m_name);
    }
}

void CacheSingle::setBarcode(QString barcode)
{
    if (m_barcode != barcode){
        m_barcode = barcode;
        emit barcodeChanged(m_barcode);
    }
}

QDataStream& operator <<(QDataStream& s, CacheSingle& d){
    return s << d.m_barcode << d.m_id << d.m_name;
}

QDataStream& operator >>(QDataStream& s, CacheSingle& d){
    return s >> d.m_barcode >> d.m_id >> d.m_name;
}
