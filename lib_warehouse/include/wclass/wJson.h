#ifndef WWJSON_H
#define WWJSON_H

#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QJsonValue>
#include "enum/wJsonEnum.h"
#include "wclass/wStatic.h"
#include "enum/wUrlEnum.h"
#include <utility>
#include "wclass/wUrlConverter.h"

class WJson : public QObject
{
public:
    explicit WJson(QObject *parent = nullptr);
    WJson(QString url, QJsonValue json, QObject *parent = nullptr);
    WJson(QJsonDocument& document, WEnum::Version version_, QObject *parent = nullptr);
    WJson(QJsonDocument& document, QObject *parent = nullptr);

    QJsonDocument toJsonDocument(WEnum::Version version = WEnum::Version_1_0) const;
    std::pair<bool, QString> fromJsonDocument(QJsonDocument document, bool isAnswer = false,
                                              WEnum::Version version_ = WUrlConverter::version());

    QString employee_id() const { return m_employee_id; }
    QString request()     const { return m_request; }
    QString url()         const { return m_url; }
    QJsonValue json()     const { return m_json; }
    QDateTime dateTime()  const { return m_dTime; }

    // answer
    int error()    { return m_error; }
    bool answer()  { return m_answer; }
    QString text() { return m_text; }

    friend QDebug operator << (QDebug d, const WJson& json);
    friend QDebug operator << (QDebug d, const WJson* json);
    static QDebug parse(QDebug d, int deep, QString key, QJsonValue value);

private:
    QString m_request;
    QString m_url;
    QString m_employee_id;
    QJsonValue m_json;
    QDateTime m_dTime;

    // answer
    int m_error;
    bool m_answer;
    QString m_text;
};

#endif // WJSON_H
