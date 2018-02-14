#ifndef NOMENCLATURESINGLE_H
#define NOMENCLATURESINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wjson.h"
#include "enum/wstatic.h"
#include "cacheSingle.h"

class NomenclatureSingle : public CacheSingle
{
    Q_OBJECT
    Q_PROPERTY(QString folder READ folder WRITE setFolder RESET resetFolder NOTIFY folderChanged)

    Q_PROPERTY(QString modelTypeId READ       modelTypeId WRITE setModelTypeId
                                   RESET resetModelTypeId NOTIFY   modelTypeIdChanged)

    Q_PROPERTY(QString consignment READ       consignment WRITE setConsignment
                                   RESET resetConsignment NOTIFY   consignmentChanged)

public:
    explicit NomenclatureSingle(QObject *parent = nullptr);
    NomenclatureSingle(const QJsonObject& obj, QObject* parent = nullptr);

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

private:
    QString m_folder;
    QString m_modelTypeId;
    QString m_consignment;
};

#endif // NOMENCLATURESINGLE_H
