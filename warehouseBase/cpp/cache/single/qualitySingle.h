#ifndef QUALITYSINGLE_H
#define QUALITYSINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wjson.h"
#include "enum/wstatic.h"
#include "cacheSingle.h"

class QualitySingle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isDefault READ       isDefault WRITE setIsDefault
                              RESET resetIsDefault NOTIFY   isDefaultChanged)

public:
    explicit QualitySingle(QObject *parent = nullptr);
    QualitySingle(const QJsonObject &obj, QObject* parent = nullptr);

    // Json ------------------------------------------------------------------------------------------------------------
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

    // READ ------------------------------------------------------------------------------------------------------------
    bool isDefault() const;

    // RESET -----------------------------------------------------------------------------------------------------------
    void resetIsDefault();

signals:
    void isDefaultChanged(bool isDefault);

public slots:
    void setIsDefault(bool isDefault);

private:
    bool m_isDefault;

};

#endif // QUALITYSINGLE_H
