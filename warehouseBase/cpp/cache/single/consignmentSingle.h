#ifndef CONSIGNMENTSINGLE_H
#define CONSIGNMENTSINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wjson.h"
#include "enum/wstatic.h"
#include "cacheSingle.h"

class ConsignmentSingle : public CacheSingle
{
    Q_OBJECT
    Q_PROPERTY(double height READ height WRITE setHeight RESET resetHeight NOTIFY heightChanged)
    Q_PROPERTY(double width  READ width  WRITE setWidth  RESET resetWidth  NOTIFY widthChanged)
    Q_PROPERTY(double lenght READ lenght WRITE setLenght RESET resetLenght NOTIFY lenghtChanged)
    Q_PROPERTY(double weight READ weight WRITE setWeight RESET resetWeight NOTIFY weightChanged)

    Q_PROPERTY(QString nomenclatureId READ       nomenclatureId WRITE setNomenclatureId
                                      RESET resetNomenclatureId NOTIFY   nomenclatureIdChanged)

    Q_PROPERTY(QString nomenclatureName READ       nomenclatureName WRITE setNomenclatureName
                                        RESET resetNomenclatureName NOTIFY   nomenclatureNameChanged)

    Q_PROPERTY(QDateTime datePacking READ       datePacking WRITE setDatePacking
                                     RESET resetDatePacking NOTIFY   datePackingChanged)

    Q_PROPERTY(QDateTime dateProduction READ       dateProduction WRITE setDateProduction
                                        RESET resetDateProduction NOTIFY   dateProductionChanged)

    Q_PROPERTY(QDateTime shelfLife READ shelfLife WRITE setShelfLife RESET resetShelfLife NOTIFY shelfLifeChanged)

public:
    explicit ConsignmentSingle(QObject *parent = nullptr);
    ConsignmentSingle(const QJsonObject& obj, QObject* parent = nullptr);

    // Json ------------------------------------------------------------------------------------------------------------
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

    // READ ------------------------------------------------------------------------------------------------------------
    double height() const { return m_height; }
    double width()  const { return m_width; }
    double lenght() const { return m_lenght; }
    double weight() const { return m_weight; }
    QString nomenclatureId()   const { return m_nomenclatureId; }
    QString nomenclatureName() const { return m_nomenclatureName; }
    QDateTime datePacking()    const { return m_datePacking; }
    QDateTime dateProduction() const { return m_dateProduction; }
    QDateTime shelfLife()      const { return m_shelfLife; }

    // RESET -----------------------------------------------------------------------------------------------------------
    void resetHeight()          { setHeight(0); }
    void resetWidth()           { setWidth (0); }
    void resetLenght()          { setLenght(0); }
    void resetWeight()          { setWeight(0); }
    void resetNomenclatureId()  { setNomenclatureId  (WStatic::guidDefault()); }
    void resetNomenclatureName(){ setNomenclatureName(WStatic::undefined()); }
    void resetDatePacking()     { setDatePacking     (WStatic::dateTimeNull()); }
    void resetDateProduction()  { setDateProduction  (WStatic::dateTimeNull()); }
    void resetShelfLife()       { setShelfLife       (WStatic::dateTimeNull()); }

signals:
    void heightChanged(double height);
    void widthChanged(double width);
    void lenghtChanged(double lenght);
    void weightChanged(double weight);
    void nomenclatureIdChanged(QString nomenclatureId);
    void nomenclatureNameChanged(QString nomenclatureName);
    void datePackingChanged(QDateTime datePacking);
    void dateProductionChanged(QDateTime dateProduction);
    void shelfLifeChanged(QDateTime shelfLife);

public slots:
    void setHeight(double height);
    void setWidth(double width);
    void setLenght(double lenght);
    void setWeight(double weight);
    void setNomenclatureId(QString nomenclatureId);
    void setNomenclatureName(QString nomenclatureName);
    void setDatePacking(QDateTime datePacking);
    void setDateProduction(QDateTime dateProduction);
    void setShelfLife(QDateTime shelfLife);

private:
    double m_height;
    double m_width;
    double m_lenght;
    double m_weight;
    QString m_nomenclatureId;
    QString m_nomenclatureName;
    QDateTime m_datePacking;
    QDateTime m_dateProduction;
    QDateTime m_shelfLife;
};

#endif // CONSIGNMENTSINGLE_H
