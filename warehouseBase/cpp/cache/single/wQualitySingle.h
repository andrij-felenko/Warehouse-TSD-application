#ifndef QUALITYSINGLE_H
#define QUALITYSINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wjson.h"
#include "enum/wstatic.h"
#include "wCacheSingle.h"

class WQualitySingle : public WCacheSingle
{
    Q_OBJECT
    Q_PROPERTY(bool isDefault READ       isDefault WRITE setIsDefault
                              RESET resetIsDefault NOTIFY   isDefaultChanged)

public:
    explicit WQualitySingle(QObject *parent = nullptr);
    WQualitySingle(const QJsonObject &obj, QObject* parent = nullptr);
    operator WCacheSingle* () { return reinterpret_cast <WCacheSingle*> (this); }

    // Json ---------------------------------------------------------------------------------------
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

    // READ ---------------------------------------------------------------------------------------
    bool isDefault() const;

    // RESET --------------------------------------------------------------------------------------
    void resetIsDefault();

signals:
    void isDefaultChanged(bool isDefault);

public slots:
    void setIsDefault(bool isDefault);

protected:
    friend QDataStream& operator << (QDataStream &s, WQualitySingle& d);
    friend QDataStream& operator >> (QDataStream &s, WQualitySingle& d);

private:
    bool m_isDefault;

};

#endif // QUALITYSINGLE_H
