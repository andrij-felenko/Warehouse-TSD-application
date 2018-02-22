#include "wSettingPrototype.h"

WSettingPrototype::WSettingPrototype(QObject *parent) : QObject(parent)
{
    m_server = new WSettingServer(this);
}

void WSettingPrototype::registerType()
{
    qmlRegisterType <WSettingServer> ("Setting_base", 1, 0, "SettingServer");
}
