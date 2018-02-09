#include "wjsonTemplate.h"
#include "singleton.h"

WJsonTemplate::WJsonTemplate(QString url, QJsonObject json, QObject *parent)
    : QObject(parent),
      m_request(WStatic::guidCreate()), m_url(url),
      m_json(json), m_dTime(QDateTime::currentDateTime())
{
    //
}

// FIXME id_employee
QJsonDocument WJsonTemplate::toJsonDocument(WEnum::Version version)
{
    QJsonObject meta;
    WJson::insert(meta, WJson::Date_time,   m_dTime.toString(Setting::get().server()->dateFormat()), version);
    WJson::insert(meta, WJson::Employee_id, WStatic::idCreate(), version);
    WJson::insert(meta, WJson::Request,     m_request, version);
    WJson::insert(meta, WJson::Url,         m_url, version);

    QJsonObject obj;
    WJson::insert(obj, WJson::Meta, QJsonValue(meta), version);
    WJson::insert(obj, WJson::Data, QJsonValue(m_json), version);

    return QJsonDocument(obj);
}
