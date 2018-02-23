#ifndef WWJSONTEMPLATE_H
#define WWJSONTEMPLATE_H

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include "enum/wJson.h"
#include "enum/wStatic.h"
#include "enum/wUrl.h"
#include <utility>

class WJsonTemplate : public QObject
{
public:
    explicit WJsonTemplate(QObject *parent = nullptr);
    WJsonTemplate(QString url, QJsonValue json, QObject *parent = nullptr);
    WJsonTemplate(QJsonDocument& document, WEnum::Version version_, QObject *parent = nullptr);
    WJsonTemplate(QJsonDocument& document, QObject *parent = nullptr);

    QJsonDocument toJsonDocument(WEnum::Version version = WJson::version()) const;
    std::pair<bool, QString> fromJsonDocument(QJsonDocument document, WEnum::Version version_ = WUrl::version());

    QString employee_id() const { return m_employee_id; }
    QString request()     const { return m_request; }
    QString url()         const { return m_url; }
    QJsonValue json()     const { return m_json; }
    QDateTime dateTime()  const { return m_dTime; }

    friend QDebug operator << (QDebug d, const WJsonTemplate& json);
    friend QDebug operator << (QDebug d, const WJsonTemplate* json);
    static QDebug parse(QDebug d, int deep, QString key, QJsonValue value);

private:
    QString m_request;
    QString m_url;
    QString m_employee_id;
    QJsonValue m_json;
    QDateTime m_dTime;
};

#endif // WJSONTEMPLATE_H
