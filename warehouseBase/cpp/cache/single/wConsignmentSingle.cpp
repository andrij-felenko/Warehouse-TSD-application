#include "wConsignmentSingle.h"
#include "wSingleton.h"

WConsignmentSingle::WConsignmentSingle(QObject *parent) : WCacheSingle(parent)
{
    //
}

WConsignmentSingle::WConsignmentSingle(const QJsonObject &obj, QObject *parent) : WConsignmentSingle(parent)
{
    fromJson(obj);
}

QJsonObject WConsignmentSingle::toJson() const
{
    QJsonObject obj = WCacheSingle::toJson();
    WJson::insert(obj, WJson::Height, m_height);
    WJson::insert(obj, WJson::Width,  m_width);
    WJson::insert(obj, WJson::Length, m_length);
    WJson::insert(obj, WJson::Weight, m_weight);
    WJson::insert(obj, WJson::Nomenclature_id, m_nomenclatureId);
    WJson::insert(obj, WJson::Nomenclature_name, m_nomenclatureName);
    WJson::insert(obj, WJson::Date_packing, m_datePacking.toString(WSetting::get().server()->dateFormat()));
    WJson::insert(obj, WJson::Date_production, m_dateProduction.toString(WSetting::get().server()->dateFormat()));
    WJson::insert(obj, WJson::ShelfLife, m_shelfLife.toString(WSetting::get().server()->dateFormat()));
    return obj;
}

void WConsignmentSingle::fromJson(const QJsonObject &obj)
{
    WCacheSingle::fromJson(obj);

    if (WJson::contains(obj, WJson::Length))
        setLength(WJson::get(obj, WJson::Length).toDouble());

    if (WJson::contains(obj, WJson::Width))
        setWidth(WJson::get(obj, WJson::Width).toDouble());

    if (WJson::contains(obj, WJson::Weight))
        setWeight(WJson::get(obj, WJson::Weight).toDouble());

    if (WJson::contains(obj, WJson::Height))
        setHeight(WJson::get(obj, WJson::Height).toDouble());

    if (WJson::contains(obj, WJson::Nomenclature_id))
        setNomenclatureId(WJson::get(obj, WJson::Nomenclature_id).toString());

    if (WJson::contains(obj, WJson::Nomenclature_name))
        setNomenclatureName(WJson::get(obj, WJson::Nomenclature_name).toString());
    else
        setNomenclatureName(WCache::get().nomenclature()->getNameById(m_nomenclatureId));

    if (WJson::contains(obj, WJson::Date_packing))
        setDatePacking(QDateTime::fromString(WJson::get(obj, WJson::Date_packing).toString(),
                                             WSetting::get().server()->dateFormat()));

    if (WJson::contains(obj, WJson::Date_production))
        setDateProduction(QDateTime::fromString(WJson::get(obj, WJson::Date_production).toString(),
                                                WSetting::get().server()->dateFormat()));

    if (WJson::contains(obj, WJson::ShelfLife))
        setShelfLife(QDateTime::fromString(WJson::get(obj, WJson::ShelfLife).toString(),
                                           WSetting::get().server()->dateFormat()));
}

void WConsignmentSingle::setHeight(double height)
{
    qWarning("Floating point comparison needs context sanity check");
    if (not qFuzzyCompare(m_height, height)){
        m_height = height;
        emit heightChanged(m_height);
    }
}

void WConsignmentSingle::setWidth(double width)
{
    qWarning("Floating point comparison needs context sanity check");
    if (not qFuzzyCompare(m_width, width)){
        m_width = width;
        emit widthChanged(m_width);
    }
}

void WConsignmentSingle::setLength(double length)
{
    qWarning("Floating point comparison needs context sanity check");
    if (not qFuzzyCompare(m_length, length)){
        m_length = length;
        emit lengthChanged(m_length);
    }
}

void WConsignmentSingle::setWeight(double weight)
{
    qWarning("Floating point comparison needs context sanity check");
    if (not qFuzzyCompare(m_weight, weight)){
        m_weight = weight;
        emit weightChanged(m_weight);
    }
}

void WConsignmentSingle::setNomenclatureId(QString nomenclatureId)
{
    if (m_nomenclatureId != nomenclatureId){
        m_nomenclatureId = nomenclatureId;
        emit nomenclatureIdChanged(m_nomenclatureId);
    }
}

void WConsignmentSingle::setNomenclatureName(QString nomenclatureName)
{
    if (m_nomenclatureName != nomenclatureName){
        m_nomenclatureName = nomenclatureName;
        emit nomenclatureNameChanged(m_nomenclatureName);
    }
}

void WConsignmentSingle::setDatePacking(QDateTime datePacking)
{
    if (m_datePacking != datePacking){
        m_datePacking = datePacking;
        emit datePackingChanged(m_datePacking);
    }
}

void WConsignmentSingle::setDateProduction(QDateTime dateProduction)
{
    if (m_dateProduction != dateProduction){
        m_dateProduction = dateProduction;
        emit dateProductionChanged(m_dateProduction);
    }
}

void WConsignmentSingle::setShelfLife(QDateTime shelfLife)
{
    if (m_shelfLife != shelfLife){
        m_shelfLife = shelfLife;
        emit shelfLifeChanged(m_shelfLife);
    }
}

QDataStream& operator << (QDataStream& s, WConsignmentSingle& d)
{
    return s << static_cast <WCacheSingle&> (d) << d.m_datePacking << d.m_dateProduction
             << d.m_height << d.m_length << d.m_nomenclatureName << d.m_nomenclatureId
             << d.m_shelfLife << d.m_weight << d.m_width;
}

QDataStream& operator >> (QDataStream& s, WConsignmentSingle& d)
{
    return s >> static_cast <WCacheSingle&> (d) >> d.m_datePacking >> d.m_dateProduction
             >> d.m_height >> d.m_length >> d.m_nomenclatureName >> d.m_nomenclatureId
             >> d.m_shelfLife >> d.m_weight >> d.m_width;
}
