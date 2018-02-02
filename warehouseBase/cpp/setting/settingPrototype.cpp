#include "settingPrototype.h"

SettingPrototype::SettingPrototype(QObject *parent) : QObject(parent)
{
    m_server = new SettingServer(this);
}

void SettingPrototype::registerType()
{
    qmlRegisterType <SettingServer> ("Setting_base", 1, 0, "SettingServer");
}
