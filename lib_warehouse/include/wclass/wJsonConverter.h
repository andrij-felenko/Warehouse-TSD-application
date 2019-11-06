#ifndef WJSONCONVERTER_H
#define WJSONCONVERTER_H

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include "enum/wJsonEnum.h"
#include "wclass/wStatic.h"

class WJsonConverter : public QObject
{
    Q_OBJECT
public:
    explicit WJsonConverter(QObject *parent = nullptr);

    static WEnum::Version version() { return WEnum::Version_1_0; }

    static bool insert(QJsonObject& obj, WJsonEnum::WJson_enum key, const QJsonValue& value_insert,
                       WEnum::Version version_ = version());
    static QString value(WJsonEnum::WJson_enum key, QString default_ = WStatic::undefined(),
                         WEnum::Version version_ = version());

    static QJsonObject createObject(WJsonEnum::WJson_enum key, const QJsonValue& value_insert,
                                    WEnum::Version version_ = version());

    static QJsonObject createObject(std::initializer_list<std::pair<WJsonEnum::WJson_enum, QJsonValue> > list,
                                    WEnum::Version version_ = version());

    static QJsonValue createValue(WJsonEnum::WJson_enum key, const QJsonValue& value_insert,
                                  WEnum::Version version_ = version());

    static QJsonValue createValue(std::initializer_list<std::pair<WJsonEnum::WJson_enum, QJsonValue> > list,
                                  WEnum::Version version_ = version());

    static QString toString(WJsonEnum::WJson_enum key, WEnum::Version version_ = version());
    static QJsonValue get(const QJsonObject& obj,  WJsonEnum::WJson_enum key, WEnum::Version version_ = version());
    static QJsonValue get(const QJsonValue& value, WJsonEnum::WJson_enum key, WEnum::Version version_ = version());
    static bool  contains(const QJsonObject& obj,  WJsonEnum::WJson_enum key, WEnum::Version version_ = version());
    static bool  contains(const QJsonValue& value, WJsonEnum::WJson_enum key, WEnum::Version version_ = version());
    static QJsonArray fromStringList(QStringList list);

public slots:
    static QString toString(int key, int version_ = version());
};

#endif // WJSONCONVERTER_H
