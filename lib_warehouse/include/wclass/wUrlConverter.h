#ifndef WURLCONVERTER_H
#define WURLCONVERTER_H

#include <QtCore/QObject>
#include "enum/wUrlEnum.h"

class WUrlConverter : public QObject
{
    Q_OBJECT
public:
    explicit WUrlConverter(QObject *parent = nullptr);

    // static variable
    static WEnum::Version version () { return     WEnum::Version_1_0; }
    static WUrlEnum::WUrl_enum errorKey();

    // static convert method
    static WUrlEnum::WUrl_enum fromInt(int key);
    static WUrlEnum::WUrl_enum fromString(QString name, WEnum::Version version_ = version());
    static QString    toString(WUrlEnum::WUrl_enum key, WEnum::Version version_ = version());

    static bool contains(WUrlEnum::WUrl_enum key);

public slots:
    static QString toString(int key, WEnum::Version version_ = version());
    static QString compareUrl(std::initializer_list <WUrlEnum::WUrl_enum> list, WEnum::Version version_ = version());
    static QString compareUrl(QList <int> list, WEnum::Version version_ = version());
    static QString compareUrl(QList <WUrlEnum::WUrl_enum> list, WEnum::Version version_ = version());
    static QList <WUrlEnum::WUrl_enum> compareUrlList(std::initializer_list<WUrlEnum::WUrl_enum> list);
    static QList <WUrlEnum::WUrl_enum> disunite(const QString& url, WEnum::Version version_ = version());
    static bool isEqual(QList <WUrlEnum::WUrl_enum> url, std::initializer_list <WUrlEnum::WUrl_enum> list);
    static int versionToInt();
};

#endif // WURLCONVERTER_H
