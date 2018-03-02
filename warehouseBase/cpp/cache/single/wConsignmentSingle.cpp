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
    WJsonConverter::insert(obj, WJsonEnum::Height, m_height);
    WJsonConverter::insert(obj, WJsonEnum::Width,  m_width);
    WJsonConverter::insert(obj, WJsonEnum::Length, m_length);
    WJsonConverter::insert(obj, WJsonEnum::Weight, m_weight);
    WJsonConverter::insert(obj, WJsonEnum::Nomenclature_id, m_nomenclatureId);
    WJsonConverter::insert(obj, WJsonEnum::Nomenclature_name, m_nomenclatureName);

    WJsonConverter::insert(obj, WJsonEnum::Date_packing,
                           m_datePacking.toString(WSetting::get().server()->dateFormat()));

    WJsonConverter::insert(obj, WJsonEnum::Date_production,
                           m_dateProduction.toString(WSetting::get().server()->dateFormat()));

    WJsonConverter::insert(obj, WJsonEnum::ShelfLife,
                           m_shelfLife.toString(WSetting::get().server()->dateFormat()));
    return obj;
}

void WConsignmentSingle::fromJson(const QJsonObject &obj)
{
    WCacheSingle::fromJson(obj);

    if (WJsonConverter::contains(obj, WJsonEnum::Length))
        setLength(WJsonConverter::get(obj, WJsonEnum::Length).toDouble());

    if (WJsonConverter::contains(obj, WJsonEnum::Width))
        setWidth(WJsonConverter::get(obj, WJsonEnum::Width).toDouble());

    if (WJsonConverter::contains(obj, WJsonEnum::Weight))
        setWeight(WJsonConverter::get(obj, WJsonEnum::Weight).toDouble());

    if (WJsonConverter::contains(obj, WJsonEnum::Height))
        setHeight(WJsonConverter::get(obj, WJsonEnum::Height).toDouble());

    if (WJsonConverter::contains(obj, WJsonEnum::Nomenclature_id))
        setNomenclatureId(WJsonConverter::get(obj, WJsonEnum::Nomenclature_id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Nomenclature_name))
        setNomenclatureName(WJsonConverter::get(obj, WJsonEnum::Nomenclature_name).toString());
    else
        setNomenclatureName(WCache::get().nomenclature()->getNameById(m_nomenclatureId));

    if (WJsonConverter::contains(obj, WJsonEnum::Date_packing))
        setDatePacking(QDateTime::fromString(WJsonConverter::get(obj, WJsonEnum::Date_packing).toString(),
                                             WSetting::get().server()->dateFormat()));

    if (WJsonConverter::contains(obj, WJsonEnum::Date_production))
        setDateProduction(QDateTime::fromString(WJsonConverter::get(obj, WJsonEnum::Date_production).toString(),
                                                WSetting::get().server()->dateFormat()));

    if (WJsonConverter::contains(obj, WJsonEnum::ShelfLife))
        setShelfLife(QDateTime::fromString(WJsonConverter::get(obj, WJsonEnum::ShelfLife).toString(),
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
