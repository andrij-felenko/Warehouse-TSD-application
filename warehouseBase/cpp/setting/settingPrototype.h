#ifndef SETTINGS_PROTOTYPE_H
#define SETTINGS_PROTOTYPE_H

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtQml/QQmlEngine>

#include "settingServer.h"

class SettingPrototype : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SettingServer* server READ server NOTIFY serverChanged)

public:
    explicit SettingPrototype(QObject *parent = nullptr);

    SettingServer* server() const { return m_server; }

    static void registerType();

private:
    SettingServer *m_server;

signals:
    void serverChanged(SettingServer* server);
};

#endif // SETTINGS_PROTOTYPE_H
