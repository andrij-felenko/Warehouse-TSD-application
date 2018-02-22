#ifndef SERVERHANDLERMANAGER_H
#define SERVERHANDLERMANAGER_H

#include <QtCore/QObject>
#include "wHandlerTemplate.h"
#include "wServerHandler.h"

class WServerHandlerManager : public QObject
{
public:
    explicit WServerHandlerManager(QObject *parent = nullptr);

    bool isUrlContains(QList <WUrl::WUrl_enum> url);
    bool isUrlContains(QString url);
    bool registrate(WHandlerTemplate* handler);
    void sendRequest(QList<WUrl::WUrl_enum> url, WJsonTemplate* json);

private:
    WServerHandler* m_baseHandler;
    QList <WHandlerTemplate*> m_list;
};

#endif // SERVERHANDLERMANAGER_H
