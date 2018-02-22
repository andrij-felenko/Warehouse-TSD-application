#ifndef SETTINGS_PROTOTYPE_H
#define SETTINGS_PROTOTYPE_H

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtQml/QQmlEngine>

#include "wSettingServer.h"

class WSettingPrototype : public QObject
{
    Q_OBJECT
    Q_PROPERTY(WSettingServer* server READ server NOTIFY serverChanged)

public:
    explicit WSettingPrototype(QObject *parent = nullptr);

    WSettingServer* server() const { return m_server; }

    static void registerType();

private:
    WSettingServer *m_server;

signals:
    void serverChanged(WSettingServer* server);
};

#endif // SETTINGS_PROTOTYPE_H
