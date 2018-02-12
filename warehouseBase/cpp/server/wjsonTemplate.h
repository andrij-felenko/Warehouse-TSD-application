#ifndef WJSONTEMPLATE_H
#define WJSONTEMPLATE_H

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include "enum/wjson.h"
#include "enum/wstatic.h"
#include <utility>

class WJsonTemplate : public QObject
{
    Q_OBJECT
public:
    WJsonTemplate(QString url, QJsonObject json, QObject *parent = nullptr);
    WJsonTemplate(QJsonDocument& document, WEnum::Version version_, QObject *parent = nullptr);
    WJsonTemplate(QJsonDocument& document, QObject *parent = nullptr);

    QJsonDocument toJsonDocument(WEnum::Version version = WJson::version()) const;
    std::pair<bool, QString> fromJsonDocument(QJsonDocument& document, WEnum::Version version_);

    QString employee_id() const { return m_employee_id; }
    QString request()     const { return m_request; }
    QString url()         const { return m_url; }
    QJsonObject json()    const { return m_json; }
    QDateTime dateTime()  const { return m_dTime; }

    friend QDebug operator << (QDebug d, const WJsonTemplate& json);
    friend QDebug operator << (QDebug d, const WJsonTemplate* json);
    static QDebug parse(QDebug d, int deep, QString key, QJsonValue value);

private:
    QString m_request;
    QString m_url;
    QString m_employee_id;
    QJsonObject m_json;
    QDateTime m_dTime;
};

#endif // WJSONTEMPLATE_H
