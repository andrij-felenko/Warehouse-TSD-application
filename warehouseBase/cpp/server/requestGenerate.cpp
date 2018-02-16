#include "requestGenerate.h"
#include "singleton.h"

RequestGenerate::RequestGenerate(QObject *parent) : QObject(parent)
{
    //
}

QJsonValue RequestGenerate::list(QStringList list)
{
    QJsonArray array;
    for (auto it : list)
        array.push_back(it);
    return WJson::createValue(WJson::List, QJsonValue(array));
}

QJsonValue RequestGenerate::empty()
{
    return QJsonValue();
}

QJsonValue RequestGenerate::date(QDateTime dateTime)
{
    return WJson::createValue(WJson::Date_time,
                              dateTime.toString(Setting::get().server()->dateFormat()));
}

QJsonValue RequestGenerate::tuple(WJson::WJson_enum key, QJsonValue value)
{
    return WJson::createValue(key, value);
}

QJsonValue RequestGenerate::reserveContainer(QString container, QString document)
{
    return WJson::createValue({ std::make_pair(WJson::Container_id, container),
                                std::make_pair(WJson::Document_id,  document) });
}

QJsonValue RequestGenerate::actualLine(QJsonObject obj, QString document)
{
    WJson::insert(obj, WJson::Document_id, document);
    return QJsonValue(obj);
}

QJsonValue RequestGenerate::removeLine(QString line, QString document)
{
    return WJson::createValue({ std::make_pair(WJson::Line_id,     line),
                                std::make_pair(WJson::Document_id, document) });
}

