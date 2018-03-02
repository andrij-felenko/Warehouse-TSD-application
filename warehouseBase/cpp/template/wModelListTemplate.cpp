#include "wModelListTemplate.h"
#include "wSingleton.h"

WModelListTemplate::WModelListTemplate(QString name, QObject *parent)
    : QAbstractListModel(parent), m_setting(), m_name(name)
{
    //
}

QHash<int, QByteArray> WModelListTemplate::roleNames() const
{
    return WEnum::getModelHash();
}

QString WModelListTemplate::name() const
{
    return m_name;
}

WEnum::Sort WModelListTemplate::sort()
{
    return static_cast <WEnum::Sort> (m_setting.value(settingModelPath("sort"),
                                                      static_cast <int> (WEnum::SortByAZ)).toInt());
}

void WModelListTemplate::p_setSort(WEnum::Sort sort_)
{
    m_setting.setValue(settingModelPath("sort"), sort_);
    update();
}

void WModelListTemplate::setSort(int sort_)
{
    p_setSort(static_cast <WEnum::Sort> (sort_));
}

QString WModelListTemplate::settingModelPath(QString nameValue)
{
    return QString("model/").append(m_name).append("/").append(nameValue);
}
