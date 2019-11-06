#include "wclass/wJsonConverter.h"
#include <QtGui/QGuiApplication>

WJsonEnum *wJsonEnum_ = new WJsonEnum(qApp);

WJsonConverter::WJsonConverter(QObject *parent) : QObject(parent)
{
    //
}

QString WJsonConverter::value(WJsonEnum::WJson_enum key, QString default_, WEnum::Version version_)
{
    return wJsonEnum_->p_value(key, default_, version_);
}

QJsonObject WJsonConverter::createObject(WJsonEnum::WJson_enum key, const QJsonValue& value_insert,
                                         WEnum::Version version_)
{
    QJsonObject obj;
    WJsonConverter::insert(obj, key, value_insert, version_);
    return obj;
}

/*!
 * \brief WJson::createObject
 * \code auto t = WJson::createObject({ std::make_pair(WJson::Name, "1"),
                                        std::make_pair(WJson::Transit, "2") });
   \endcode
 * \param list
 * \param version_
 * \return
 */
QJsonObject WJsonConverter::createObject(std::initializer_list<std::pair <WJsonEnum::WJson_enum, QJsonValue>> list,
                                WEnum::Version version_)
{
    QJsonObject obj;
    for (auto it : list)
        WJsonConverter::insert(obj, it.first, it.second, version_);
    return obj;
}

QJsonValue WJsonConverter::createValue(WJsonEnum::WJson_enum key, const QJsonValue& value_insert,
                                       WEnum::Version version_)
{
    return QJsonValue(WJsonConverter::createObject(key, value_insert, version_));
}

QJsonValue WJsonConverter::createValue(std::initializer_list<std::pair <WJsonEnum::WJson_enum, QJsonValue>> list,
                              WEnum::Version version_)
{
    return QJsonValue(WJsonConverter::createObject(list, version_));
}

QString WJsonConverter::toString(WJsonEnum::WJson_enum key, WEnum::Version version_)
{
    return WJsonConverter::value(key, WStatic::undefined(), version_);
}

QString WJsonConverter::toString(int key, int version_)
{
    return WJsonConverter::toString(static_cast <WJsonEnum::WJson_enum> (key), static_cast <WEnum::Version> (version_));
}

QJsonValue WJsonConverter::get(const QJsonObject& obj, WJsonEnum::WJson_enum key, WEnum::Version version_)
{
    return obj.value(WJsonConverter::toString(key, version_));
}

QJsonValue WJsonConverter::get(const QJsonValue& value, WJsonEnum::WJson_enum key, WEnum::Version version_)
{
    return WJsonConverter::get(value.toObject(), key, version_);
}

bool WJsonConverter::contains(const QJsonObject& obj, WJsonEnum::WJson_enum key, WEnum::Version version_)
{
    return obj.contains(WJsonConverter::toString(key, version_));
}

bool WJsonConverter::contains(const QJsonValue& value, WJsonEnum::WJson_enum key, WEnum::Version version_)
{
    return WJsonConverter::contains(value.toObject(), key, version_);
}

QJsonArray WJsonConverter::fromStringList(QStringList list)
{
    QJsonArray array;
    for (auto it : list)
        array.push_back(it);
    return array;
}

bool WJsonConverter::insert(QJsonObject& obj, WJsonEnum::WJson_enum key, const QJsonValue& value_insert,
                  WEnum::Version version_)
{
    if (WStatic::undefined() != WJsonConverter::toString(key, version_)){
        obj.insert(WJsonConverter::toString(key, version_), value_insert);
        return true;
    }
    return false;
}
