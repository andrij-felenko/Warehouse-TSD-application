#include "server/wRequestGenerate.h"
#include "wSingleton.h"

WRequestGenerate::WRequestGenerate(QObject *parent) : QObject(parent)
{
    //
}

QJsonValue WRequestGenerate::list(QStringList list)
{
    QJsonArray array;
    for (const auto &it : list)
        array.push_back(it);
    return WJsonConverter::createValue(WJsonEnum::List, QJsonValue(array));
}

QJsonValue WRequestGenerate::empty()
{
    return QJsonValue();
}

QJsonValue WRequestGenerate::date(QDateTime dateTime)
{
    qDebug() << dateTime.toString(WSetting::get().server()->dateFormat())
             << dateTime
             << WSetting::get().server()->dateFormat();
    return WJsonConverter::createValue(WJsonEnum::Date_time,
                              dateTime.toString(WSetting::get().server()->dateFormat()));
}

QJsonValue WRequestGenerate::tuple(int key, QJsonValue value)
{
    return WJsonConverter::createValue(static_cast <WJsonEnum::WJson_enum> (key), value);
}

QJsonValue WRequestGenerate::reserveContainer(QString container, QString document)
{
    return WJsonConverter::createValue({ std::make_pair(WJsonEnum::Container_id, container),
                                std::make_pair(WJsonEnum::Document_id,  document) });
}

QJsonValue WRequestGenerate::actualLine(QJsonObject obj, QString document)
{
    WJsonConverter::insert(obj, WJsonEnum::Document_id, document);
    return QJsonValue(obj);
}

QJsonValue WRequestGenerate::removeLine(QString line, QString document)
{
    return WJsonConverter::createValue({ std::make_pair(WJsonEnum::Line_id,     line),
                                         std::make_pair(WJsonEnum::Document_id, document) });
}

