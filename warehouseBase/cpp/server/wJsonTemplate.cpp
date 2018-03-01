#include "wJsonTemplate.h"
#include "wSingleton.h"

WJsonTemplate::WJsonTemplate(QObject *parent)
    : QObject(parent),
      m_request(WStatic::guidCreate()), m_url(""), m_employee_id(WUser::get().current()->id()),
      m_json(QJsonObject()), m_dTime(QDateTime::currentDateTime()),
      m_error(-1), m_answer(false), m_text(QString(""))
{
    //
}

WJsonTemplate::WJsonTemplate(QString url, QJsonValue json, QObject *parent)
    : WJsonTemplate(parent)
{
    m_url = url;
    m_json = json;
}

WJsonTemplate::WJsonTemplate(QJsonDocument &document, WEnum::Version version_, QObject *parent)
    : WJsonTemplate(parent)
{
    fromJsonDocument(document, version_);
}

WJsonTemplate::WJsonTemplate(QJsonDocument &document, QObject *parent)
    : WJsonTemplate(parent)
{
    fromJsonDocument(document, WUrl::version());
}

QJsonDocument WJsonTemplate::toJsonDocument(WEnum::Version version) const
{
    QJsonObject meta;
    WJson::insert(meta, WJson::Date_time,   m_dTime.toString(WSetting::get().server()->dateFormat()), version);
    WJson::insert(meta, WJson::Employee_id, m_employee_id, version);
    WJson::insert(meta, WJson::Request,     m_request, version);
    WJson::insert(meta, WJson::Url,         m_url, version);

    QJsonObject obj;
    WJson::insert(obj, WJson::Meta, QJsonValue(meta), version);
    WJson::insert(obj, WJson::Data, QJsonValue(m_json), version);

    return QJsonDocument(obj);
}

std::pair <bool, QString> WJsonTemplate::fromJsonDocument(QJsonDocument document, bool isAnswer,
                                                          WEnum::Version version_)
{
    if (isAnswer)
        m_request = WStatic::guidDefault();

    auto obj = document.object();
    if (not WJson::contains(obj, WJson::Meta, version_))
        return std::make_pair(false, QObject::tr("Meta field not found"));

    if (isAnswer){
        if (not WJson::contains(obj, WJson::Answer, version_))
            return std::make_pair(false, "Answer field not found");

        if (not WJson::contains(obj, WJson::Error, version_))
            return std::make_pair(false, "Error field not found");

        if (not WJson::contains(obj, WJson::Text, version_))
            return std::make_pair(false, "Text field not found");
    }

    QJsonObject metaData = WJson::get(document.object(), WJson::Meta, version_).toObject();
    if (not WJson::contains(metaData, WJson::Request, version_))
        return std::make_pair(false, QObject::tr("Meta field request not found"));

    if (not WJson::contains(metaData, WJson::Url, version_))
        return std::make_pair(false, QObject::tr("Meta field url not found"));

    m_dTime = QDateTime::fromString(WJson::get(metaData, WJson::Date_time, version_).toString(),
                                    WSetting::get().server()->dateFormat());
    m_employee_id = WJson::get(metaData, WJson::Employee_id, version_).toString();
    m_request     = WJson::get(metaData, WJson::Request,     version_).toString();
    m_url         = WJson::get(metaData, WJson::Url,         version_).toString();
    m_json        = WJson::get(obj,      WJson::Data,        version_);

    if (isAnswer){
        m_answer = WJson::get(obj, WJson::Answer, version_).toBool();
        m_error = WJson::get(obj, WJson::Error, version_).toInt();
        m_text = WJson::get(obj, WJson::Text, version_).toString();
    }

    return std::make_pair(true, QString());
}

QDebug operator << (QDebug d, const WJsonTemplate& json)
{
    d.noquote();
    d << QString("Request ").leftJustified(120, '_') << "\n";
    d << "Meta:\n";
    d << "    date:   " << json.dateTime().toString("yyyy.MM.dd dddd") << "\n";
    d << "    time:   " << json.dateTime().toString("hh:mm:ss:zzz") << "\n";
    d << "    request:" << json.request() << "\n";
    d << "    url:    " << json.url() << " [" << WSetting::get().server()->domain() + json.url() << "]\n";
    d << "Data:" << "\n";
    WJsonTemplate::parse(d, 0, "", QJsonValue(json.json()));
    d << QString().leftJustified(120, '-') << '\n';
    return d;
}

QDebug WJsonTemplate::parse(QDebug d, int deep, QString key, QJsonValue value)
{
    d << QString(deep * 4, ' ');
    if (not key.isEmpty())
        d << key.append(" : ");

    if (value.isArray()){
        d << "[";
        if (value.toArray().count() != 0)
            d << "\n";
        for (auto it : value.toArray())
            WJsonTemplate::parse(d, deep + 1, "", it);
        d << QString(deep * 4, ' ').append("]") << "\n";
    }
    else if (value.isObject()){
        d << "{" << "\n";
        for (QString keyIt : value.toObject().keys()){
            WJsonTemplate::parse(d, deep + 1, keyIt, value.toObject().value(keyIt));
        }
        d << QString(deep * 4, ' ').append(" }") << "\n";
    }
    else if (value.isBool())
        d << (value.toBool() ? "true" : "false") << "\n";
    else if (value.isDouble())
        d << value.toDouble() << "\n";
    else if (value.isString())
        d << value.toString() << "\n";
    return d;
}

QDebug operator << (QDebug d, const WJsonTemplate* json)
{
    return d << *json;
}
