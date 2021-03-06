#include "cache/single/wCacheSingle.h"
#include "enum/wJsonEnum.h"
#include "wclass/wStatic.h"
#include "wclass/wJsonConverter.h"

/*!
 * \brief По умолчанию.
 * \param parent ссылка на родительский обьект
 */
WCacheSingle::WCacheSingle(QObject* parent) : QObject(parent)
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
WCacheSingle::WCacheSingle(const QJsonObject& obj, QObject* parent) : WCacheSingle(parent)
{
    fromJson(obj);
}

/*!
 * \brief Копирование класа в json-обьект
 * \return json-копию элемента кэша
 */
QJsonObject WCacheSingle::toJson() const
{
    QJsonObject obj;
    WJsonConverter::insert(obj, WJsonEnum::Id,      m_id);
    WJsonConverter::insert(obj, WJsonEnum::Name,    m_name);
    WJsonConverter::insert(obj, WJsonEnum::Barcode, m_barcode);
    return obj;
}

/*!
 * \brief Запись параметров с переданого json-обьекта
 * \param obj json-обьект с новыми значениями параметров
 */
void WCacheSingle::fromJson(const QJsonObject& obj)
{
    resetAll();
    if (WJsonConverter::contains(obj, WJsonEnum::Id))
        setId(WJsonConverter::get(obj, WJsonEnum::Id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Name))
        setName(WJsonConverter::get(obj, WJsonEnum::Name).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Barcode))
        setBarcode(WJsonConverter::get(obj, WJsonEnum::Barcode).toString());
}

/*!
 * \brief Запрос на идентификатор
 * \return Идентификатор
 */
QString WCacheSingle::id() const
{
    return m_id;
}

/*!
 * \brief Запрос на имя
 * \return Имя
 */
QString WCacheSingle::name() const
{
    return m_name;
}

/*!
 * \brief Запрос на штрихкод
 * \return Штрихкод
 */
QString WCacheSingle::barcode() const
{
    return m_barcode;
}

bool WCacheSingle::isEmpty() const
{
    return m_id == WStatic::guidDefault();
}

/*! \brief Сброс всех параметров на значения по умолчанию */
void WCacheSingle::resetAll()
{
    resetBarcode();
    resetId();
    resetName();
}

/*! \brief Сброс штрихкода на пустое значение */
void WCacheSingle::resetBarcode()
{
    setBarcode(WStatic::undefined());
}

/*! \brief Сброс идентификатора на пустой идентификатор */
void WCacheSingle::resetId()
{
    setId(WStatic::guidDefault());
}

/*! \brief Сброс имени на имя по умолчанию */
void WCacheSingle::resetName()
{
    setName(WStatic::undefined());
}

/*!
 * \brief Установка нового идентификатора
 * \param id Идентификатор
 */
void WCacheSingle::setId(QString id)
{
    if (m_id != id){
        m_id = id;
        emit idChanged(m_id);
    }
}

/*!
 * \brief Установка нового имени
 * \param name Имя
 */
void WCacheSingle::setName(QString name)
{
    if (m_name != name){
        m_name = name;
        emit nameChanged(m_name);
    }
}

/*!
 * \brief Установка нового штрихкода
 * \param barcode Штрихкод
 */
void WCacheSingle::setBarcode(QString barcode)
{
    if (m_barcode != barcode){
        m_barcode = barcode;
        emit barcodeChanged(m_barcode);
    }
}

/*!
 * \brief operator << запись данных класса в поток
 * \param s Обьект потока данных
 * \param d Клас из которого идет запись данных в поток
 * \return Адрес потока в точке конца записаных данных
 */
QDataStream& operator <<(QDataStream& s, WCacheSingle& d){
    return s << d.m_barcode << d.m_id << d.m_name;
}

/*!
 * \brief operator >> чтение данных с потока в класс
 * \param s Обьект потока данных
 * \param d Клас в который идет считываение данных с потока
 * \return Адрес потока в точке конца считывания данных
 */
QDataStream& operator >>(QDataStream& s, WCacheSingle& d){
    return s >> d.m_barcode >> d.m_id >> d.m_name;
}
