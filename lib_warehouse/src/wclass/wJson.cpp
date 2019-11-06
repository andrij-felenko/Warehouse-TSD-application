#include "wclass/wJson.h"
#include "wSingleton.h"

WJson::WJson(QObject *parent)
    : QObject(parent),
      m_request(WStatic::guidCreate()), m_url(""), m_employee_id(WUser::get().current()->id()),
      m_json(QJsonObject()), m_dTime(QDateTime::currentDateTime()),
      m_error(-1), m_answer(false), m_text(QString(""))
{
    //
}

WJson::WJson(QString url, QJsonValue json, QObject *parent)
    : WJson(parent)
{
    m_url = url;
    m_json = json;
}

WJson::WJson(QJsonDocument &document, WEnum::Version version_, QObject *parent)
    : WJson(parent)
{
    fromJsonDocument(document, version_);
}

WJson::WJson(QJsonDocument &document, QObject *parent)
    : WJson(parent)
{
    fromJsonDocument(document, WUrlConverter::version());
}

QJsonDocument WJson::toJsonDocument(WEnum::Version version) const
{
    QJsonObject meta;
    WJsonConverter::insert(meta, WJsonEnum::Date_time,
                           m_dTime.toString(WSetting::get().server()->dateFormat()),
                           version);
    WJsonConverter::insert(meta, WJsonEnum::Employee_id, m_employee_id, version);
    WJsonConverter::insert(meta, WJsonEnum::Request,     m_request, version);
    WJsonConverter::insert(meta, WJsonEnum::Url,         m_url, version);

    QJsonObject obj;
    WJsonConverter::insert(obj, WJsonEnum::Meta, QJsonValue(meta), version);
    WJsonConverter::insert(obj, WJsonEnum::Data, QJsonValue(m_json), version);

    return QJsonDocument(obj);
}

std::pair <bool, QString> WJson::fromJsonDocument(QJsonDocument document, bool isAnswer,
                                                          WEnum::Version version_)
{
    if (isAnswer)
        m_request = WStatic::guidDefault();

    auto obj = document.object();
    if (not WJsonConverter::contains(obj, WJsonEnum::Meta, version_))
        return std::make_pair(false, QObject::tr("Meta field not found"));

    if (isAnswer){
        if (not WJsonConverter::contains(obj, WJsonEnum::Answer, version_))
            return std::make_pair(false, "Answer field not found");

        if (not WJsonConverter::contains(obj, WJsonEnum::Error, version_))
            return std::make_pair(false, "Error field not found");

        if (not WJsonConverter::contains(obj, WJsonEnum::Text, version_))
            return std::make_pair(false, "Text field not found");
    }

    QJsonObject metaData = WJsonConverter::get(document.object(), WJsonEnum::Meta, version_).toObject();
    if (not WJsonConverter::contains(metaData, WJsonEnum::Request, version_))
        return std::make_pair(false, QObject::tr("Meta field request not found"));

    if (not WJsonConverter::contains(metaData, WJsonEnum::Url, version_))
        return std::make_pair(false, QObject::tr("Meta field url not found"));

    m_dTime = QDateTime::fromString(WJsonConverter::get(metaData, WJsonEnum::Date_time, version_).toString(),
                                    WSetting::get().server()->dateFormat());
    m_employee_id = WJsonConverter::get(metaData, WJsonEnum::Employee_id, version_).toString();
    m_request     = WJsonConverter::get(metaData, WJsonEnum::Request,     version_).toString();
    m_url         = WJsonConverter::get(metaData, WJsonEnum::Url,         version_).toString();
    m_json        = WJsonConverter::get(obj,      WJsonEnum::Data,        version_);

    if (isAnswer){
        m_answer = WJsonConverter::get(obj, WJsonEnum::Answer, version_).toBool();
        m_error = WJsonConverter::get(obj, WJsonEnum::Error, version_).toInt();
        m_text = WJsonConverter::get(obj, WJsonEnum::Text, version_).toString();
    }

    return std::make_pair(true, QString());
}

QDebug operator << (QDebug d, const WJson& json)
{
    d.noquote();
    d << QString("Request ").leftJustified(120, '_') << "\n";
    d << "Meta:\n";
    d << "    date:   " << json.dateTime().toString("yyyy.MM.dd dddd") << "\n";
    d << "    time:   " << json.dateTime().toString("hh:mm:ss:zzz") << "\n";
    d << "    request:" << json.request() << "\n";
    d << "    url:    " << json.url() << " [" << WSetting::get().server()->domain() + json.url() << "]\n";
    d << "Data:" << "\n";
    WJson::parse(d, 0, "", QJsonValue(json.json()));
    d << QString().leftJustified(120, '-') << '\n';
    return d;
}

QDebug WJson::parse(QDebug d, int deep, QString key, QJsonValue value)
{
    d << QString(deep * 4, ' ');
    if (not key.isEmpty())
        d << key.append(" : ");

    if (value.isArray()){
        d << "[";
        if (value.toArray().count() != 0)
            d << "\n";
        for (auto it : value.toArray())
            WJson::parse(d, deep + 1, "", it);
        d << QString(deep * 4, ' ').append("]") << "\n";
    }
    else if (value.isObject()){
        d << "{" << "\n";
        for (QString keyIt : value.toObject().keys()){
            WJson::parse(d, deep + 1, keyIt, value.toObject().value(keyIt));
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

QDebug operator << (QDebug d, const WJson* json)
{
    return d << *json;
}
