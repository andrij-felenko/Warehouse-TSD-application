#include "wUrlConverter.h"
#include <QtGui/QGuiApplication>

WUrlEnum *wUrlEnum_ = new WUrlEnum(qApp);

WUrlConverter::WUrlConverter(QObject *parent) : QObject(parent)
{
    //
}

WUrlEnum::WUrl_enum WUrlConverter::errorKey()
{
    return wUrlEnum_->p_errorKey();
}

WUrlEnum::WUrl_enum WUrlConverter::fromInt(int key)
{
    if (not wUrlEnum_->p_contains(static_cast <WUrlEnum::WUrl_enum> (key)))
        return WUrlEnum::WUrl_enum::___;
    return static_cast <WUrlEnum::WUrl_enum> (key);
}

WUrlEnum::WUrl_enum WUrlConverter::fromString(QString name, WEnum::Version version_)
{
    return wUrlEnum_->p_fromString(name, version_);
}

QString WUrlConverter::toString(WUrlEnum::WUrl_enum key, WEnum::Version version_)
{
    return wUrlEnum_->p_toString(key, version_);
}

QString WUrlConverter::toString(int key, WEnum::Version version_)
{
    return wUrlEnum_->p_toString(static_cast <WUrlEnum::WUrl_enum> (key), version_);
}

bool WUrlConverter::contains(WUrlEnum::WUrl_enum key)
{
    return wUrlEnum_->p_contains(key);
}

QString WUrlConverter::compareUrl(std::initializer_list <WUrlEnum::WUrl_enum> list, WEnum::Version version_)
{
    QString ret("");
    for (auto it : list)
        ret += toString(it, version_);
    return ret;
}

QString WUrlConverter::compareUrl(QList<int> list, WEnum::Version version_)
{
    QString ret("");
    for (auto it : list)
        ret += toString(static_cast <WUrlEnum::WUrl_enum> (it), version_);
    return ret;
}

QString WUrlConverter::compareUrl(QList <WUrlEnum::WUrl_enum> list, WEnum::Version version_)
{
    QString ret("");
    for (auto it : list)
        ret += toString(it, version_);
    return ret;
}

QList <WUrlEnum::WUrl_enum> WUrlConverter::compareUrlList(std::initializer_list <WUrlEnum::WUrl_enum> list)
{
    QList <WUrlEnum::WUrl_enum> url;
    for (auto it : list)
        url.push_back(it);
    return url;
}

QList <WUrlEnum::WUrl_enum> WUrlConverter::disunite(const QString& url, WEnum::Version version_)
{
    QList<WUrlEnum::WUrl_enum> list;
    QString value("");
    for (int i = 0; i < url.length(); i++){
        if (url[i].isUpper() and not value.isEmpty()){
            auto key = fromString(value, version_);
            if (key != errorKey())
                list.push_back(key);
            value.clear();
            value += url[i];
        }
        else if (i + 1 == url.length()){
            value += url[i];
            auto key = fromString(value, version_);
            if (key != errorKey())
                list.push_back(key);
        }
        else
            value += url[i];
    }
    return list;
}

bool WUrlConverter::isEqual(QList<WUrlEnum::WUrl_enum> url, std::initializer_list <WUrlEnum::WUrl_enum> list)
{
    return url == compareUrlList(list);
}

int WUrlConverter::versionToInt()
{
    return static_cast <int> (WUrlConverter::version());
}
