#ifndef WCACHESINGLE_H
#define WCACHESINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

/*! \brief Информация про один элемент кэша */
class WCacheSingle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ       id WRITE setId
                          RESET resetId NOTIFY   idChanged)

    Q_PROPERTY(QString name READ       name WRITE setName
                            RESET resetName NOTIFY   nameChanged)

    Q_PROPERTY(QString barcode READ       barcode WRITE setBarcode
                               RESET resetBarcode NOTIFY   barcodeChanged)

public:
    WCacheSingle(QObject* parent = nullptr);
    WCacheSingle(const QJsonObject &obj, QObject* parent = nullptr);

    // Json ----------------------------------------------------------------------------------------
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

    QString id() const;
    QString name() const;
    QString barcode() const;
    bool isEmpty() const;

    // RESET ---------------------------------------------------------------------------------------
    void resetBarcode();
    void resetId();
    void resetName();

public slots:
    void setId(QString id);
    void setName(QString name);
    void setBarcode(QString barcode);

protected:
    void resetAll();

signals:
    void idChanged(QString id);           ///< Оповещает про смену идентификатора
    void nameChanged(QString name);       ///< Оповещает про смену имени
    void barcodeChanged(QString barcode); ///< Оповещает про смену штрихкода

protected:
    friend QDataStream& operator << (QDataStream &s, WCacheSingle &d);
    friend QDataStream& operator >> (QDataStream &s, WCacheSingle &d);

private:
    QString m_id;      ///< Идентификатор ячейки
    QString m_name;    ///< Наименование ячейки
    QString m_barcode; ///< Штрихкод ячейки
};

#endif // CACHESINGLE_H
