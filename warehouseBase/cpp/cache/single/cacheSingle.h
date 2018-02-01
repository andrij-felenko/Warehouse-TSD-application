#ifndef CACHESINGLE_H
#define CACHESINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "json.h"
#include "static.h"

/*! \brief Информация про один элемент кэша */
class CacheSingle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ       id WRITE setId
                          RESET resetId NOTIFY   idChanged)

    Q_PROPERTY(QString name READ       name WRITE setName
                            RESET resetName NOTIFY   nameChanged)

    Q_PROPERTY(QString barcode READ       barcode WRITE setBarcode
                               RESET resetBarcode NOTIFY   barcodeChanged)

public:
    CacheSingle(QObject* parent = nullptr);
    CacheSingle(const QJsonObject &obj, QObject* parent = nullptr);

    // Json ----------------------------------------------------------------------------------------
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

    QString id() const;
    QString name() const;
    QString barcode() const;

    // RESET ---------------------------------------------------------------------------------------
    void resetAll();
    void resetBarcode();
    void resetId();
    void resetName();

public slots:
    void setId(QString id);
    void setName(QString name);
    void setBarcode(QString barcode);

signals:
    void idChanged(QString id);           ///< Оповещает про смену идентификатора
    void nameChanged(QString name);       ///< Оповещает про смену имени
    void barcodeChanged(QString barcode); ///< Оповещает про смену штрихкода

protected:
    friend QDataStream& operator << (QDataStream &s, CacheSingle &d);
    friend QDataStream& operator >> (QDataStream &s, CacheSingle &d);

private:
    QString m_id;      ///< Идентификатор ячейки
    QString m_name;    ///< Наименование ячейки
    QString m_barcode; ///< Штрихкод ячейки
};

#endif // CACHESINGLE_H
