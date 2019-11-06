#ifndef WSERVERHANDLERMANAGER_H
#define WSERVERHANDLERMANAGER_H

#include <QtCore/QObject>
#include "wHandlerTemplate.h"
#include "wServerHandler.h"

class WServerHandlerManager : public QObject
{
public:
    explicit WServerHandlerManager(QObject *parent = nullptr);

    bool isUrlContains(QList <WUrlEnum::WUrl_enum> url);
    bool isUrlContains(QString url);
    bool registrate(WHandlerTemplate* handler);
    void sendRequest(QList<WUrlEnum::WUrl_enum> url, WJson* json);

private:
    WServerHandler* m_baseHandler;
    QList <WHandlerTemplate*> m_list;
};

#endif // SERVERHANDLERMANAGER_H
