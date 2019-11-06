#ifndef WNOMENCLATURESINGLE_H
#define WNOMENCLATURESINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wJsonEnum.h"
#include "wclass/wStatic.h"
#include "wCacheSingle.h"

class WNomenclatureSingle : public WCacheSingle
{
    Q_OBJECT
    Q_PROPERTY(QString folder READ folder WRITE setFolder RESET resetFolder NOTIFY folderChanged)

    Q_PROPERTY(QString modelTypeId READ       modelTypeId WRITE setModelTypeId
                                   RESET resetModelTypeId NOTIFY   modelTypeIdChanged)

    Q_PROPERTY(QString consignment READ       consignment WRITE setConsignment
                                   RESET resetConsignment NOTIFY   consignmentChanged)

public:
    explicit WNomenclatureSingle(QObject *parent = nullptr);
    WNomenclatureSingle(const QJsonObject& obj, QObject* parent = nullptr);
    operator WCacheSingle* () { return reinterpret_cast <WCacheSingle*> (this); }

    // Json ----------------------------------------------------------------------------------------
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

    // READ ----------------------------------------------------------------------------------------
    QString folder() const;
    QString modelTypeId() const;
    QString consignment() const;

    // RESET ---------------------------------------------------------------------------------------
    void resetFolder();
    void resetModelTypeId();
    void resetConsignment();

signals:
    void folderChanged(QString folder);
    void modelTypeIdChanged(QString modelTypeId);
    void consignmentChanged(QString consignment);

public slots:
    void setFolder(QString folder);
    void setModelTypeId(QString modelTypeId);
    void setConsignment(QString consignment);

protected:
    friend QDataStream& operator << (QDataStream &s, WNomenclatureSingle& d);
    friend QDataStream& operator >> (QDataStream &s, WNomenclatureSingle& d);

private:
    QString m_folder;
    QString m_modelTypeId;
    QString m_consignment;
};

#endif // NOMENCLATURESINGLE_H
