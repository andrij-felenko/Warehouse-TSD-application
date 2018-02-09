#ifndef WJSONTEMPLATE_H
#define WJSONTEMPLATE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "enum/wjson.h"
#include "enum/wstatic.h"

class WJsonTemplate : public QObject
{
    Q_OBJECT
public:
    WJsonTemplate(QString url, QJsonObject json, QObject *parent = nullptr);

    QJsonDocument toJsonDocument(WEnum::Version version = WJson::version());

    QString request()    { return m_request; }
    QString url()        { return m_url; }
    QJsonObject json()   { return m_json; }
    QDateTime dateTime() { return m_dTime; }

private:
    QString m_request;
    QString m_url;
    QJsonObject m_json;
    QDateTime m_dTime;
};

#endif // WJSONTEMPLATE_H
