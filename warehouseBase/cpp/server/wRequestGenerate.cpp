#include "wRequestGenerate.h"
#include "wSingleton.h"

WRequestGenerate::WRequestGenerate(QObject *parent) : QObject(parent)
{
    //
}

QJsonValue WRequestGenerate::list(QStringList list)
{
    QJsonArray array;
    for (auto it : list)
        array.push_back(it);
    return WJson::createValue(WJson::List, QJsonValue(array));
}

QJsonValue WRequestGenerate::empty()
{
    return QJsonValue();
}

QJsonValue WRequestGenerate::date(QDateTime dateTime)
{
    return WJson::createValue(WJson::Date_time,
                              dateTime.toString(WSetting::get().server()->dateFormat()));
}

QJsonValue WRequestGenerate::tuple(WJson::WJson_enum key, QJsonValue value)
{
    return WJson::createValue(key, value);
}

QJsonValue WRequestGenerate::reserveContainer(QString container, QString document)
{
    return WJson::createValue({ std::make_pair(WJson::Container_id, container),
                                std::make_pair(WJson::Document_id,  document) });
}

QJsonValue WRequestGenerate::actualLine(QJsonObject obj, QString document)
{
    WJson::insert(obj, WJson::Document_id, document);
    return QJsonValue(obj);
}

QJsonValue WRequestGenerate::removeLine(QString line, QString document)
{
    return WJson::createValue({ std::make_pair(WJson::Line_id,     line),
                                std::make_pair(WJson::Document_id, document) });
}

