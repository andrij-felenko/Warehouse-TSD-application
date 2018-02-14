#include "consignmentSingle.h"
#include "singleton.h"

ConsignmentSingle::ConsignmentSingle(QObject *parent) : CacheSingle(parent)
{
    //
}

ConsignmentSingle::ConsignmentSingle(const QJsonObject &obj, QObject *parent) : ConsignmentSingle(parent)
{
    fromJson(obj);
}

QJsonObject ConsignmentSingle::toJson() const
{
    QJsonObject obj = CacheSingle::toJson();
    WJson::insert(obj, WJson::Height, m_height);
    WJson::insert(obj, WJson::Width,  m_width);
    WJson::insert(obj, WJson::Length, m_lenght);
    WJson::insert(obj, WJson::Weight, m_weight);
    WJson::insert(obj, WJson::Nomenclature_id, m_nomenclatureId);
    WJson::insert(obj, WJson::Nomenclature_name, m_nomenclatureName);
    WJson::insert(obj, WJson::Date_packing, m_datePacking.toString(Setting::get().server()->dateFormat()));
    WJson::insert(obj, WJson::Date_production, m_dateProduction.toString(Setting::get().server()->dateFormat()));
    WJson::insert(obj, WJson::ShelfLife, m_shelfLife.toString(Setting::get().server()->dateFormat()));
    return obj;
}

void ConsignmentSingle::fromJson(const QJsonObject &obj)
{
    CacheSingle::fromJson(obj);

    if (WJson::contains(obj, WJson::Length))
        setLenght(WJson::get(obj, WJson::Length).toDouble());

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
        setNomenclatureName(Cache::get().nomenclature()->getNameById(m_nomenclatureId));

    if (WJson::contains(obj, WJson::Date_packing))
        setDatePacking(QDateTime::fromString(WJson::get(obj, WJson::Date_packing).toString(),
                                             Setting::get().server()->dateFormat()));

    if (WJson::contains(obj, WJson::Date_production))
        setDateProduction(QDateTime::fromString(WJson::get(obj, WJson::Date_production).toString(),
                                                Setting::get().server()->dateFormat()));

    if (WJson::contains(obj, WJson::ShelfLife))
        setShelfLife(QDateTime::fromString(WJson::get(obj, WJson::ShelfLife).toString(),
                                           Setting::get().server()->dateFormat()));
}

void ConsignmentSingle::setHeight(double height)
{
    qWarning("Floating point comparison needs context sanity check");
    if (not qFuzzyCompare(m_height, height)){
        m_height = height;
        emit heightChanged(m_height);
    }
}

void ConsignmentSingle::setWidth(double width)
{
    qWarning("Floating point comparison needs context sanity check");
    if (not qFuzzyCompare(m_width, width)){
        m_width = width;
        emit widthChanged(m_width);
    }
}

void ConsignmentSingle::setLenght(double lenght)
{
    qWarning("Floating point comparison needs context sanity check");
    if (not qFuzzyCompare(m_lenght, lenght)){
        m_lenght = lenght;
        emit lenghtChanged(m_lenght);
    }
}

void ConsignmentSingle::setWeight(double weight)
{
    qWarning("Floating point comparison needs context sanity check");
    if (not qFuzzyCompare(m_weight, weight)){
        m_weight = weight;
        emit weightChanged(m_weight);
    }
}

void ConsignmentSingle::setNomenclatureId(QString nomenclatureId)
{
    if (m_nomenclatureId != nomenclatureId){
        m_nomenclatureId = nomenclatureId;
        emit nomenclatureIdChanged(m_nomenclatureId);
    }
}

void ConsignmentSingle::setNomenclatureName(QString nomenclatureName)
{
    if (m_nomenclatureName != nomenclatureName){
        m_nomenclatureName = nomenclatureName;
        emit nomenclatureNameChanged(m_nomenclatureName);
    }
}

void ConsignmentSingle::setDatePacking(QDateTime datePacking)
{
    if (m_datePacking != datePacking){
        m_datePacking = datePacking;
        emit datePackingChanged(m_datePacking);
    }
}

void ConsignmentSingle::setDateProduction(QDateTime dateProduction)
{
    if (m_dateProduction != dateProduction){
        m_dateProduction = dateProduction;
        emit dateProductionChanged(m_dateProduction);
    }
}

void ConsignmentSingle::setShelfLife(QDateTime shelfLife)
{
    if (m_shelfLife != shelfLife){
        m_shelfLife = shelfLife;
        emit shelfLifeChanged(m_shelfLife);
    }
}
