#include "setting/wSettingPrototype.h"

WSettingPrototype::WSettingPrototype(QObject *parent) : QObject(parent)
{
    m_server = new WSettingServer(this);
}
