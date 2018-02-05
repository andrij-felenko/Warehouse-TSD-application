#include "cacheSingle.h"
#include "enum/wjson.h"
#include "enum/wstatic.h"

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

/*!
 * \brief Копирование класа в json-обьект
 * \return json-копию элемента кэша
 */
QJsonObject CacheSingle::toJson() const
{
    QJsonObject obj;
    WJson::insert(obj, WJson::Id,      m_id);
    WJson::insert(obj, WJson::Name,    m_name);
    WJson::insert(obj, WJson::Barcode, m_barcode);
    return obj;
}

/*!
 * \brief Запись параметров с переданого json-обьекта
 * \param obj json-обьект с новыми значениями параметров
 */
void CacheSingle::fromJson(const QJsonObject& obj)
{
    resetAll();
    if (WJson::contains(obj, WJson::Id))      setId     (WJson::get(obj, WJson::Id)     .toString());
    if (WJson::contains(obj, WJson::Name))    setName   (WJson::get(obj, WJson::Name)   .toString());
    if (WJson::contains(obj, WJson::Barcode)) setBarcode(WJson::get(obj, WJson::Barcode).toString());
}

/*!
 * \brief Запрос на идентификатор
 * \return Идентификатор
 */
QString CacheSingle::id() const
{
    return m_id;
}

/*!
 * \brief Запрос на имя
 * \return Имя
 */
QString CacheSingle::name() const
{
    return m_name;
}

/*!
 * \brief Запрос на штрихкод
 * \return Штрихкод
 */
QString CacheSingle::barcode() const
{
    return m_barcode;
}

/*! \brief Сброс всех параметров на значения по умолчанию */
void CacheSingle::resetAll()
{
    resetBarcode();
    resetId();
    resetName();
}

/*! \brief Сброс штрихкода на пустое значение */
void CacheSingle::resetBarcode()
{
    setBarcode(WStatic::undefined());
}

/*! \brief Сброс идентификатора на пустой идентификатор */
void CacheSingle::resetId()
{
    setId(WStatic::guidDefault());
}

/*! \brief Сброс имени на имя по умолчанию */
void CacheSingle::resetName()
{
    setName(WStatic::undefined());
}

/*!
 * \brief Установка нового идентификатора
 * \param id Идентификатор
 */
void CacheSingle::setId(QString id)
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
void CacheSingle::setName(QString name)
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
void CacheSingle::setBarcode(QString barcode)
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
QDataStream& operator <<(QDataStream& s, CacheSingle& d){
    return s << d.m_barcode << d.m_id << d.m_name;
}

/*!
 * \brief operator >> чтение данных с потока в класс
 * \param s Обьект потока данных
 * \param d Клас в который идет считываение данных с потока
 * \return Адрес потока в точке конца считывания данных
 */
QDataStream& operator >>(QDataStream& s, CacheSingle& d){
    return s >> d.m_barcode >> d.m_id >> d.m_name;
}
